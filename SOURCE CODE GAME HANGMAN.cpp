#include <iostream>// for input and output
#include <conio.h>//for getch and system cls
#include <windows.h>//for colour
#include <cstdlib>//buat list
#include <ctime>//buat mengakses waktu
#include <string.h>//buat sensitive case
#include <unistd.h>// for usleep function
using namespace std;

typedef char infotype;
typedef struct TElmt *address;
typedef struct TElmt{
	infotype info;
	address next;
} Elmt;

struct List{
	address first;
};

#define First(L) (L).first
#define Next(P) (P)->next
#define Info(P)(P)->info
#define Nil NULL

void CreateEmpty(List *L){
	(*L).first=NULL;
}

bool IsEmpty(List L){
	return ((L).first==NULL);
}

address Allocation(infotype x){
	address NewElmt;	
	NewElmt = (Elmt*) malloc(sizeof(Elmt));
	NewElmt->info = x;
	NewElmt->next = NULL;
	
	return NewElmt;
}

void Deallocation(address hapus){
	free(hapus);
}

void InsertFirst(List *L, infotype x){
	address NewElmt;
	NewElmt = Allocation(x);
	
	if(NewElmt != NULL){
		if(IsEmpty(*L)){
			(*L).first = NewElmt;
		}
		else{
			NewElmt->next = (*L).first;
			(*L).first = NewElmt;
		}
	}
}

void InsertAfter(address *PredElmt, infotype x){
	address NewElmt;
	NewElmt = Allocation(x);
	
	if(NewElmt != NULL){
		NewElmt->next = (*PredElmt)->next;
		(*PredElmt)->next=NewElmt;
	}
}

void InsertLast(List *L, infotype x){
	if (IsEmpty(*L)) InsertFirst(&(*L), x);
	else {
		address temp;
		temp = (*L).first;
		
		while(temp->next!=NULL) temp = temp->next;
		
		InsertAfter(&temp, x);
	}
}

void Output(List L){
	if(!IsEmpty(L)){
		address temp =First(L);
		while(Next(temp)!=NULL){
			cout<<Info(temp) <<" ";
			temp = Next(temp);
		}
		cout<<Info(temp);
	}
}

void cekhuruf(List *L1, List *L2, string x, int *m){
	char a=x[0];
	address P1=First(*L1), P2=First(*L2);
	while(Next(P1)!=NULL){
			if(Info(P1)==a){
				Info(P2)=a;
				*m=1;
			}
			P1 = Next(P1);
			P2 = Next(P2);
		}
		if(Info(P1)==a){
		Info(P2)=a;
		*m=1;
		}
}


void cekkata(List L1, List *L2, string x, int *z){
	address P1=First(L1), P2=First(*L2);
	int i=0,j=0;
	*z=1;
	while(i<x.length()){
		if(Info(P1)==x[i]){
			j++;
		}
		P1=Next(P1);
		i++;
	}
	if (j!=i){
		*z=0;
	}else{
		*z=1;
	}
}

const char rocket[] =
"           _\n\
          /^\\\n\
          |-|\n\
          |H|\n\
          |A|\n\
          |N|\n\
          |G|\n\
          |M|\n\
         /|A|\\\n\
        / |N| \\\n\
       |  |*|  |\n\
        `-\"\"\"-`\n\
";

int setcolor (unsigned short color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}

int gotoxy (int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void convert (string &s) {
    for (int i=0; i<s.length(); i++){
         s[i] = tolower(s[i]);
    }
}

void gambar (){

	gotoxy (5,8);cout << "  I===  " ;
	gotoxy (5,9);cout << "  I  O  " ;
	gotoxy (5,10);cout << "  I -|- " ;
	gotoxy (5,11);cout << "  I / / " ;

}
void petunjuk (){
		system("cls");
		setcolor (128);
		
		gotoxy (14,4); cout << "                                                                                          ";
		gotoxy (13,5); cout << "                                How to Play Game Hangman?                                   ";
		gotoxy (13,6); cout << "                                                                                            ";
		gotoxy (13,7); cout << "   1. You will choose, will play this game with your friend or computer                     ";
		gotoxy (13,8); cout << "   2. If you play this game with the computer, then you will guess the word                 "; 
		gotoxy (13,9); cout << "      chosen by the program                                                                 ";
		gotoxy (13,9); cout << "   3. If you play this game with your friend, You and your friends will enter the           ";
		gotoxy (13,10);cout << "      name as a guesser and give guesses. Then, you or your friends will input the          "; 
		gotoxy (13,11);cout << "      words that one of you must guess                                                      ";
		gotoxy (13,12);cout << "   4. The chance to guess is 4 times                                                        ";
		gotoxy (13,13);cout << "   5. The guesser can immediately guess the word that has been determined                   ";
		gotoxy (13,14);cout << "   6. If you succed in guessing the first word, the game continues to guess the next        ";
		gotoxy (13,15);cout << "      word. If you lose, the game will end .                                                ";
		gotoxy (14,16);cout << "                                                                                          ";
		
}

int skor=0;
void single(){
	List L1,L2,L3;
	srand((unsigned)time(0));
	int x=rand();
	string A[10]={"crocodile", "rabbit", "buffalo", "giraffe", "butterfly","turtle", "kangaroo", "elephant", "dragonfly", "ladybird"};
	string hangman,masuk;
	
	system("cls");
	setcolor(11);
	
	CreateEmpty(&L1);
	CreateEmpty(&L2);
	CreateEmpty(&L3);
	hangman = A[x%9];
	int z=0, kesempatan=4;
					
	for(int i=0; i<hangman.length(); i++){
		gotoxy(20,8); InsertLast(&L1,hangman[i]);
	}
	for(int i=0; i<hangman.length(); i++){
		gotoxy(20,8); InsertLast(&L2,'#');
	}
					
	while(kesempatan>0){
		gotoxy(10,7); cout<<"\t\t\tWrong Letter : ";Output(L3);
		cout<<endl<<endl;
						
		Output(L2);cout<<"\t\t\tChance : "<<kesempatan<<endl;
		kesempatan--;
		int m=0;
					
		cin>>masuk;
		convert(masuk);
		
		if(masuk.length()==1){
			cekhuruf(&L1,&L2,masuk,&m);
		}else if(masuk.length()==hangman.length()){
			cekkata(L1,&L2,masuk,&z);
		}
					
		system("cls");
		if(m==0){
			InsertLast(&L3,masuk[0]);
		}
				
		if(z==1){
			break;
			getch();
			system ("cls"); 
		}
					
	}
	cout<<endl;
			
	setcolor(7);
	gotoxy(10,5); cout << "                   " ; Output(L2); cout << "                      ";
	gotoxy(10,6); cout << "   The word is : ";
	Output(L1); 
	
	if(z==1){
		string pilihan;
		skor = skor+100;
		setcolor(180);
					
		gotoxy(15,8); cout << "       CONGRATULATION!!!       ";
		gotoxy(15,9); cout << "                 YOU WIN       ";
		gotoxy(15,10);cout << "                               ";
		gotoxy(15,11);cout << "     YOUR SCORE IS "<< skor << "         ";
		
		gotoxy(15,20);cout << "98(Next)\t99(Quit)";
		gotoxy(15,21);cin  >> pilihan;
					
		if(pilihan=="98"){
		setcolor(10);
		system ("cls");
		single();
			
		}else{
		setcolor(10);
		system ("cls");
		}
	}else{
		setcolor(71);
		gambar();	
		gotoxy(15,8); cout << "                               ";
		gotoxy(15,9); cout << "          GAME OVER            ";
		gotoxy(15,10);cout << "                               ";
		gotoxy(15,11);cout << "       YOUR SCORE IS "<< skor << "       ";
						
		getch();
	}
		setcolor(10);
}

void dobel(){
	
	List L1,L2,L3;
	
	CreateEmpty(&L1);
	CreateEmpty(&L2);
	CreateEmpty(&L3);
	
	string main1, main2, kata, jawab;
	int z=0, kesempatan=4;
	
	system("cls");
	setcolor (11);
	
	cout << "Your Name " << endl;
	cin >> main1;
	cout << "Your Friend's Name "<< endl;
	cin >> main2;

	cout << main1 << " the word to guess is ? "<< endl;
	cin >> kata;
	
	for(int i=0; i<kata.length(); i++){
		InsertLast(&L1,kata[i]);
	}
	for(int i=0; i<kata.length(); i++){
		InsertLast(&L2,'#');
	}
	
	for (int i=0; i<30; i++){
		cout << endl;
	}
	
	while(kesempatan>0){
		gotoxy(10,7); cout<<"\t\t\tWrong Letter : ";Output(L3);
		cout<<endl<<endl;
	
		Output(L2);cout<<"\t\t\tChance : "<<kesempatan<<endl;
		kesempatan--;
		int m=0;
					
		cin>>jawab;
		convert(jawab);
	
		if(jawab.length()==1){
			cekhuruf(&L1,&L2,jawab,&m);
		}else if(jawab.length()==kata.length()){
			cekkata(L1,&L2,jawab,&z);
		}
	
		system("cls");
		if(m==0){
			InsertLast(&L3,jawab[0]);
		}
				
		if(z==1){
			break;
			getch();
			system ("cls"); 
		}
					
	}
	cout<<endl;
	
	setcolor(7);

	gotoxy(10,5); cout << "                   " ; Output(L2); cout << "                      ";
	gotoxy(10,6); cout << "   The word is : ";
	Output(L1); 
	
	if(z==1){
		setcolor(180);
	
		gotoxy(15,8); cout << "      CONGRATULATION!!!        ";
		gotoxy(15,9); cout << "                YOU WIN        ";
		gotoxy(15,10);cout << "                               ";
	
		setcolor(10);
		getch();
		system ("cls");
	}else{
		setcolor(71);
	
		gotoxy(15,8); cout << "                               ";
		gotoxy(15,9); cout << "          GAME OVER            ";
		gotoxy(15,10);cout << "                               ";
	
		getch();
	} 
	setcolor(10);
}

void roket(){
	
	for (int i = 0; i < 50; i ++) cout<<"\n"; // jump to bottom of console
    cout<<rocket;
    int j = 300000;
    for (int i = 0; i < 50; i ++) {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout<<"\n"; // move rocket a line upward
    }
}
		


void menu(){
	string pilihan, pemain;
	system ("cls"); setcolor (3);
	
	cout << endl << endl;
	cout << "			                                                                       " << endl;
	cout << "				           **WELCOME TO GAME HANGMAN**           " << endl;
	cout << "			                                                                       " << endl;
	
	gotoxy(11,7); cout << "                          ";	
	gotoxy(11,8); cout << "         **MENU**         ";
	gotoxy(11,9); cout << "                          ";
	gotoxy(11,10);cout << " 1. How to Play?          ";
	gotoxy(11,11);cout << " 2. Play Game             ";
	gotoxy(11,12);cout << " 3. Quit Game             ";
	gotoxy(11,13);cout << "                          ";
	
	gotoxy(13,17); cout << "    Your Choice :   ";
		
	cin >> pilihan;
	
	if(pilihan=="1"){
		roket();
		petunjuk();
		
		setcolor(10);
		getch();
		menu();
	} else if(pilihan=="2"){
		roket();
		system("cls");
		setcolor(8);
		
		gotoxy (15,13); cout << "I want to play with ?";
		gotoxy (15,15); cout << "1. Me vs Komputer";
		gotoxy (15,16); cout << "2. Me vs My Friend";
		
		gotoxy (15,19); cout << " Pilihan Anda = ";
		cin >> pemain;
		
		if (pemain == "1"){
			single();
		}else if (pemain == "2"){
			roket();
			dobel();		
		}
		else {
			gotoxy(17,21); cout << "Sorry, this option doesn't exist";
			
			setcolor (10);
			menu();
		}
		setcolor (10);
		menu();
	}
	else if (pilihan=="3"){
		gotoxy(45,44); cout << "                                 ";
		gotoxy(45,45); cout << "        **FINISH, THANKYOU**     ";
		gotoxy(45,46); cout << "                                 ";
	} else {
		gotoxy (14,20); cout << "Sorry, this option doesn't exist ";
		getch();
		setcolor (10);
		menu();
	}
	
}

void loading (){
	char a=177, b=219; 
	for(int i=0;i<=25;i++)
	gotoxy(30,16);cout<<a;
	
	Sleep(200);
	cout<<"\r";
	cout<<"\t\t\t\t\t ";
   gotoxy (17,5);cout<<"      ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»";cout<<endl;
   gotoxy (17,6);cout<<"      ºÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,7);cout<<"  ÉÍÍÍ¼ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÈÍÍÍ»";cout<<endl;
   gotoxy (17,8); cout<<" É¼ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÈ»";cout<<endl;
   gotoxy (17,9);cout<<" ºÛÛÛÛÛÛÛÛÛÛÛÛÛÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»ÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,10);cout<<" ºÛÛÛÛÛÛÛÛÛÛÛÛÛº                                                ºÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,11);cout<<" ºÛÛÛÛÉÍÍÍ»ÛÛÛÛº                                                ºÛÛÛÛÉÍÍÍ»ÛÛÛÛº";cout<<endl;
   gotoxy (17,12);cout<<" ºÛÛÛÛº   ºÛÛÛÛº                                                ºÛÛÛÛº   ºÛÛÛÛº";cout<<endl;
   gotoxy (17,13);cout<<" ºÛÉÍÍ¼   ÈÍÍ»Ûº                                                ºÛÉÍÍ¼   ÈÍÍ»Ûº";cout<<endl;
   gotoxy (17,14);cout<<" ºÛº         ºÛº               HANGMAN Loading....              ºÛº         ºÛº";cout<<endl;
   gotoxy (17,15);cout<<" ºÛº         ºÛº                                                ºÛº         ºÛº";cout<<endl;
   gotoxy (17,16);cout<<" ºÛÈÍÍ»   ÉÍÍ¼Ûº                                                ºÛÈÍÍ»   ÉÍÍ¼Ûº";cout<<endl;
   gotoxy (17,17);cout<<" ºÛÛÛÛº   ºÛÛÛÛº                                                ºÛÛÛÛº   ºÛÛÛÛº";cout<<endl;
   gotoxy (17,18);cout<<" ºÛÛÛÛÈÍÍÍ¼ÛÛÛÛº                                                ºÛÛÛÛÈÍÍÍ¼ÛÛÛÛº";cout<<endl;
   gotoxy (17,19);cout<<" ºÛÛÛÛÛÛÛÛÛÛÛÛÛº                                                ºÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,20);cout<<" ºÛÛÛÛÛÛÛÛÛÛÛÛÛº                                                ºÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,21);cout<<" ºÛÛÛÛÛÛÛÛÛÛÛÛÛÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,22);cout<<" È»ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÉ¼";cout<<endl;
   gotoxy (17,23);cout<<"  ÈÍÍÍ»ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÉÍÍÍ¼";cout<<endl;
   gotoxy (17,24);cout<<"      ºÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛº";cout<<endl;
   gotoxy (17,25);cout<<"      ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼";cout<<endl;
	gotoxy(45,16);
	
	for(int i=0;i<=25;i++){
		cout<<b;
		Sleep(200);
	
	}
}

int main (){

	setcolor(2);
	

	gotoxy (30,15); loading();
	menu();
	
	return 0;
	
}
