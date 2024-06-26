/*
  Roco's default kart editor. Based on Ermelber's, MKDasher's and Yami's
  MKDS ARM9 Music Table Editor 1.0
*/


#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <streambuf>
#include <cerrno>
#include <cstdlib>
#include <ctype.h>
#include <stdint.h>
typedef int32_t		s32;
typedef s32 fx32;
#define FX32_SHIFT          12
#define FX32_INT_SIZE       19
#define FX32_DEC_SIZE       12

#define FX32_INT_MASK       0x7ffff000
#define FX32_DEC_MASK       0x00000fff
#define FX32_SIGN_MASK      0x80000000

#define FX32_MAX            ((fx32)0x7fffffff)
#define FX32_MIN            ((fx32)0x80000000)

#define FX_MUL(v1, v2)       ((fx32)(((fx64)(v1) * (v2) + 0x800LL) >> FX32_SHIFT))
#define FX_MUL32x64C(v1, v2) ((fx32)(((v2) * (v1) + 0x80000000LL) >> 32))

#define FX_FX32_TO_F32(x)    ((f32)((x) / (f32)(1 << FX32_SHIFT)))
#define FX_F32_TO_FX32(x)    ((fx32)(((x) > 0) ? \
                                     ((x) * (1 << FX32_SHIFT) + 0.5f ) : \
                                     ((x) * (1 << FX32_SHIFT) - 0.5f )))

#define FX32_CONST(x)        FX_F32_TO_FX32(x)

using namespace std;

string get_file_contents(const char *filename) {
	ifstream in (filename, ios::in | ios::binary);
	if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		
		return (contents.str());
	}  else {
				cout << "There isn't a valid file called ''arm9.bin'' in your directory.\nCheck if it really is there.\n";
				cin.ignore();			
				exit(1);
			}
}

int min(int a, int b){
 if (a < b) return a;
 else return b;
}

int main() {
    const int defoffset = 0x153274;
    const int ordoffset = 1389420;
    const int rainoff = 535424;
    const int snowoff = 535416;
    const int balloonYoff = 0x156600;
    int table;
    int next = 0;
    int offset;
    int selected;
    int newvalue;
    char choice;
    string chars[13];
    int a[211];
    fx32 *ballonY[13];
    //character names
    chars[0] = "Mario";
    chars[1] = "DK";
    chars[2] = "Toad";
    chars[3] = "Bowser";
    chars[4] = "Peach";
    chars[5] = "Wario";
    chars[6] = "Yoshi";
    chars[7] = "Luigi";
    chars[8] = "Dry Bones";
    chars[9] = "Daisy";
    chars[10] = "Waluigi";
    chars[11] = "ROB";
    chars[12] = "Shy Guy";
    
    //Start
    printf("Roco's default kart editor\n\nSpecial thanks to Ermelber, Yami, MKDasher and Szymbar without them this wouldn't be possible\nPress enter to continue\n\n");
    cin.ignore();   
    //ask which table to edit
	while (next == 0)
	{
		printf("What table do you want to edit?\n1=Default kart\n2=Kart order in menu\n3= Rain Slot\n4= Snow Slot\n5 = Balloon Y offset\n:");
		scanf("%d",&table);
		switch (table){
			case 1:
				offset = defoffset;
				next = 1;
				break;
			case 2:
				offset = ordoffset;
				next = 1;
				break;
            case 3:
				offset = rainoff;
				next = 1;
				break;
            case 4:
				offset = snowoff;
				next = 1;
				break;
			case 5:
				offset = balloonYoff;
				next = 1;
				break;
			default:
				printf("invalid option. Please try again\n");
		}
	 } 
    //Get arm9.bin
    string text = get_file_contents("arm9.bin");
    for (int i = offset; i < min(text.size(), offset + 211); i++)
        a[i-offset] = (int) text[i];
	if (table == 1){       
    do
    {
        //Print chars       
        for (int i = 0; i < 13; i++){
            cout << i << ") "<< chars[i] <<" [" << a[i*4] <<"]" << endl;
        }
        //Select slot
        do{
            printf("\n\nSelect a character to change [0..12]: ");
            scanf("%d",&selected);        
        }while (selected <0 || selected>12); 
    
        //Confirm
        while (true) {
            cout << "\nDo you want to change " << chars[selected] << " default kart? [Y/N] ";
            cin >> choice;
        //Choices
            if ((choice == 'Y') || (choice == 'y')) {
                do{
                    //New value
                    printf("If you want to know what kart id you should enter here, please visit: https://bit.ly/3fHDHNi\nNote:Kart ID 36 will crash the game.\n");
                    cout << "\nInsert the new kart id (Old value was " << a[selected*4] << ") [0..36]=";
                    scanf("%d",&newvalue);
                }while (newvalue <0 || newvalue>36);
                a[selected*4]=newvalue;
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    
        
        while (true) {
            cout << "\nDo you want to edit it furthermore? [Y/N] ";
            cin >> choice;

            if ((choice == 'Y') || (choice == 'y')) {
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    }
    while (choice == 'Y' || choice == 'y'); 
}else if(table == 3 || table == 4){
	do
    {
        //Print each entry      
        
    selected = 0;
        //Confirm
                do{
                    //New value
                    printf("Enter the course ID for this weather's slot\n");
                    cout << "\nInsert the new course id (Old value was " << a[selected*4] << ") [1..54]=";
                    scanf("%d",&newvalue);
                }while (newvalue <1 || newvalue>54);
                a[selected*4]=newvalue;
            

    
        
        while (true) {
            cout << "\nDo you want to edit it furthermore? [Y/N] ";
            cin >> choice;

            if ((choice == 'Y') || (choice == 'y')) {
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    }
    while (choice == 'Y' || choice == 'y'); 
}else if (table == 5){       
	for (int i = offset; i < min(text.size(), offset + 211); i+=4)
        a[i-offset] = (s32) text[i];
    do
    {
        //Print chars       
        for (int i = 0; i < 13; i++){
            cout << i << ") "<< chars[i] <<" [" << a[i*4] <<"]" << endl;
        }
        //Select slot
        do{
            printf("\n\nSelect a character to change [0..12]: ");
            scanf("%d",&selected);        
        }while (selected <0 || selected>12); 
    
        //Confirm
        while (true) {
            cout << "\nDo you want to change " << chars[selected] << " default kart? [Y/N] ";
            cin >> choice;
        //Choices
            if ((choice == 'Y') || (choice == 'y')) {
                do{
                    //New value
                    printf("If you want to know what kart id you should enter here, please visit: https://bit.ly/3fHDHNi\nNote:Kart ID 36 will crash the game.\n");
                    cout << "\nInsert the new kart id (Old value was " << a[selected*4] << ") [0..36]=";
                    scanf("%d",&newvalue);
                }while (newvalue <0 || newvalue>36);
                a[selected*4]=newvalue;
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    
        
        while (true) {
            cout << "\nDo you want to edit it furthermore? [Y/N] ";
            cin >> choice;

            if ((choice == 'Y') || (choice == 'y')) {
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    }
    while (choice == 'Y' || choice == 'y'); 
}else{
	do
    {
        //Print each entry      
        for (int i = 0; i < 36; i++){
            cout << "entry " << i <<": [" << a[i*4] <<"]" << endl;
        }
        //Select slot
        do{
            printf("\n\nSelect an entry to change [0..35]: ");
            scanf("%d",&selected);        
        }while (selected <0 || selected>35); 
    
        //Confirm
        while (true) {
            cout << "\nDo you want to change entry number " << selected << " ? [Y/N] ";
            cin >> choice;
        //Choices
            if ((choice == 'Y') || (choice == 'y')) {
                do{
                    //New value
                    printf("If you want to know what kart id you should enter here, please visit: https://bit.ly/3fHDHNi\nNote:Kart ID 36 will crash the game.\n");
                    cout << "\nInsert the new kart id (Old value was " << a[selected*4] << ") [0..36]=";
                    scanf("%d",&newvalue);
                }while (newvalue <0 || newvalue>36);
                a[selected*4]=newvalue;
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    
        
        while (true) {
            cout << "\nDo you want to edit it furthermore? [Y/N] ";
            cin >> choice;

            if ((choice == 'Y') || (choice == 'y')) {
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    }
    while (choice == 'Y' || choice == 'y'); 
}
    
    /*//Prints array (Testing purposes)
    for (int i=0; i<211; i++)
        cout << a[i] << endl;
    cin.ignore();*/
    
    //Make backup and overwrite arm9.bin
    ofstream out( "arm9.bin.bak", std::ios_base::binary | std::ios_base::out );
    out << text;
    out.close();
    for (int i = offset; i < min(text.size(), offset + 211); i++)
        text[i] = a[i-offset];    
    out.open( "arm9.bin", std::ios_base::binary | std::ios_base::out );
    out << text;
    out.close();
    	
	cout << "\nSuccessfully saved edited_arm9.bin in your folder!\nPress ENTER to exit the program :3\n";
    cin.ignore();
    cin.ignore();    
    //end
    return 0;
}
