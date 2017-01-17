#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//function declaration
int menuScreen();
void helpPage();
void endPage();
int receiveUser();
void miniHelp();
int playScreen();
void boardGenerate();
int typemove();
int checkpresent();
int checkpiecetype();


//check user moves
int kingcheck();
int queencheck();
int knightcheck();
int bishopcheck();
int rookcheck();
int pawncheck();

//check user movable
int movable();

//pc function
int pcmove();
int pcmovable();

//void pcrookcheck();
int pcrookcheck();
void pcknightcheck();
int random_moves();
int king_random_moves();
int search();
int pawnnum(char);
int possiblemove(char type);


//declard global array
char word[8] = {'a','b','c','d','e','f','g','h'};
char board[8][8] = {'R','N','B','Q','K','B','N','R','!','@','#','$','%','^','&','*',0,'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','1','2','3','4','5','6','7','8','r','n','b','q','k','b','n','r'};
char original[8][8] = {'R','N','B','Q','K','B','N','R','!','@','#','$','%','^','&','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','1','2','3','4','5','6','7','8','r','n','b','q','k','b','n','r'};
bool pawnmoved[8];
bool pcpawnmoved[8] = {false,false,false,false,false,false,false,false};
int pomoves1[35];
int pomoves2[35];
int king1[8];
int king2[8];
int stuck;
int win = 0;
int played = 0;


//global variables
int fx,fy,tx,ty;
int pfx,pfy,ptx,pty;

//main function
int main(){
	int end = 0;
//	boardGenerate();
	while(end == 0){
		end = menuScreen();
	}

//end whole program	
	return 0;
}

//menu screen
int menuScreen(){
	int again;
	string menvar ="top";
	
		//while menvar is the following 4 commands
		while(menvar != "start" && menvar != "end" && (menvar == "top" || menvar == "menu")){
			//show menu page with command for user to type in
			cout<<"CHESS GAME~~~~~~~"<<endl<<endl;
			cout<<"Menu Screen"<<endl<<endl;
			cout<<"Type the following command:"<<endl<<"menu: open up the help page"<<endl<<"top: show the top score"<<endl<<"start: start the chess game"<<endl<<"end: quit the game"<<endl;
			//get command
			cin>>menvar;
			
			//error check
			while(menvar != "start" && menvar != "end" && menvar != "top" && menvar != "menu"){
				cout<<"enter a valid command please: ";
				cin>>menvar;
			}
		
			//if "top"
			if (menvar == "top"){
				//show top score
				//documentation????????
				cout<<"The top score is: 0."<<endl<<endl;
			}
			//if "menu"
			else if (menvar == "menu"){
				//show help page
				cout<<endl;
				helpPage();
			}
		}
		//if "end"
		if(menvar == "end"){
			//show end page
			endPage();
			//end program
			return 1;
		}
		
			//if "start"
		if(menvar == "start"){
			//show play screem
			win = 0;
			if(played == 1){
				for(int i = 0;i<8;i++){
					pawnmoved[i] = 0;
					pcpawnmoved[i] = false;
					for(int j = 0;j<8;j++){
						board[i][j] = original[i][j];
					}
				}
			}
			played = 0;
			again = playScreen();
			//stop playing
			if (again == 0){
				return 1;
			}
			//go to quit screen and back again to continue
			else if (again == 1){
				played = 1;
				return 0;
			}
		}
}

//help page (from main menu)
void helpPage(){
	cout<<"HELP PAGE::::"<<endl<<endl;
	cout<<"Goal: eat your opponent's king!"<<endl<<endl;
	cout<<"Command while playing:"<<endl;
	cout<<"Enter move: Enter you move by the format e.g.: \"a3 d3\", which means \"move the piece in a3 to d3.\""<<endl;
	cout<<"Quit from the game: enter \"quit\""<<endl;
	cout<<"Need mini help in game: enter \"help\""<<endl;
	cout<<"Give up the game: enter \"up\""<<endl;
	cout<<"Enter a move: enter \"move\""<<endl<<endl;
	cout<<"Moves for each pieces: "<<endl;
	cout<<"King (k): one square in any direction."<<endl;
	cout<<"Root (r): move any number of squares along any rank or file, but may not leap over other pieces."<<endl;
	cout<<"Bishop (b): move any number of squares diagonally, but may not leap over other pieces."<<endl;
	cout<<"Queen (q): can move any number of squares along rank, file, or diagonal, but it may not leap over other pieces."<<endl;
	cout<<"Knight (n): moves to any of the closest squares that are not on the same rank, file, or diagonal, thus the move forms an \"L\"-shape, can leap over other pieces."<<endl;
	cout<<"Pawn (p): first move can move 1 or 2 boxes forward, after moved once, it can only move forward by 1 step."<<endl<<"Capture an opponent's piece on a square diagonally in front of it on an adjacent file, by moving to that square."<<endl;
	cout<<"If the pawn reach the opposite bound, it can change its type to queen, knight, rook, or bishop."<<endl;
	cout<<endl<<endl;
}

//end page
void endPage(){
	cout<<"Thank you for playing!!!"<<endl;
}

//play screen
int playScreen(){
	int usergo,stopplaying,gosecond = 1;
	int command;
	char yesno,yesno2;
	//ask user go first or second
	cout<<"You want to go first or second? (1/2): ";
	cin>>usergo;
	//error check
	while (usergo != 1 && usergo != 2){
		cout<<"Enter a valid number please. (1/2): ";
		cin>>usergo;
	}
	
	//set user go first or second
	//second
	if(usergo == 2){
		gosecond = 2;
	}
	//first
	else if(usergo == 1){
		gosecond = 1;
	}
	
	if(gosecond == 1){
	//user go first
	while(usergo == 1){
//if nowuser = 1{
		command = receiveUser();
	//help (mini help menu)
		if(command == 1){
			miniHelp();
		}
		
	//up (give up)
		else if (command == 2){
			//reconfirm give up
			cout<<"Are you really want to give up? (y/n) "<<endl;
			cin>>yesno;
			//error check
			while (yesno !='y' && yesno!= 'n'){
				cout<<"Please re-enter again: (y/n) ";
				cin>>yesno;
			}
			//if really give up
			if (yesno == 'y'){
				//show lose msg
				cout<<"You lose!!!"<<endl;
				//ask play again?
				cout<<"Do you want to play again? (y/n) ";
				cin>>yesno;
				//error check
				while(yesno != 'y' && yesno != 'n'){
					cout<<"Please enter again (y/n): ";
					cin>>yesno;
				}
				//if don't want to play again
				if(yesno == 'n'){
					//go to ending page, set stopplaying to 1
					stopplaying = 1;
					endPage();
					return 0;
				}
				//if want to play again
				else if(yesno == 'y'){
					//back to the menu screen, set stopplaying to 0
					stopplaying = 0;
					return 1;
				}
			}
			//if not really want to give up
			else if(yesno == 'n'){
				//do nothing, back to the game by enter command
			}
		}
		
	//quit
		else if(command == 3){
			cout<<"Do you want to quit without save?";
			cin>>yesno2;
			while(yesno2 != 'y' && yesno2 != 'n'){
				cout<<"Please re-enter again (y/n): ";
				cin>>yesno2;
			}
			if(yesno2 == 'y'){
				stopplaying = 1;
				cout<<"saving..."<<endl;
				endPage();
				return 0;
			}
			else if(yesno2 == 'n'){
				stopplaying = 1;
				//expect to do saving
				
				endPage();
				return 0;
			}
		}
		
	//move	
		else if(command == 4){
			usergo = typemove();
			//user win
			if(win == 1){
				boardGenerate();
				cout<<"You win!!!!"<<endl;
				
				cout<<"Do you want to play again? (y/n) ";
				cin>>yesno;
				//error check
				while(yesno != 'y' && yesno != 'n'){
					cout<<"Please enter again (y/n): ";
					cin>>yesno;
				}
				//if don't want to play again
				if(yesno == 'n'){
					//go to ending page, set stopplaying to 1
					stopplaying = 1;
					endPage();
					return 0;
				}
				//if want to play again
				else if(yesno == 'y'){
					//back to the menu screen, set stopplaying to 0
					stopplaying = 0;
					return 1;
				}
			}
			if (usergo == 0){
				pcmove();
				//pc win
				if(win == 2){
					boardGenerate();
					cout<<"You lose......"<<endl;
					
					cout<<"Do you want to play again? (y/n) ";
					cin>>yesno;
					//error check
					while(yesno != 'y' && yesno != 'n'){
						cout<<"Please enter again (y/n): ";
						cin>>yesno;
					}
					//if don't want to play again
					if(yesno == 'n'){
						//go to ending page, set stopplaying to 1
						stopplaying = 1;
						endPage();
						return 0;
					}
					//if want to play again
					else if(yesno == 'y'){
						//back to the menu screen, set stopplaying to 0
						stopplaying = 0;
						return 1;
					}
				}
				usergo = 1;      //if user go second, here will be  still usergo = 1 (in another part)
			}
		}
	}
	}
	else if(gosecond == 2){
		pcmove();
		usergo = 1;
		while(usergo == 1){
//if nowuser = 1{
		command = receiveUser();
	//help (mini help menu)
		if(command == 1){
			miniHelp();
		}
		
	//up (give up)
		else if (command == 2){
			//reconfirm give up
			cout<<"Are you really want to give up? (y/n) "<<endl;
			cin>>yesno;
			//error check
			while (yesno !='y' && yesno!= 'n'){
				cout<<"Please re-enter again: (y/n) ";
				cin>>yesno;
			}
			//if really give up
			if (yesno == 'y'){
				//show lose msg
				cout<<"You lose!!!"<<endl;
				//ask play again?
				cout<<"Do you want to play again? (y/n) ";
				cin>>yesno;
				//error check
				while(yesno != 'y' && yesno != 'n'){
					cout<<"Please enter again (y/n): ";
					cin>>yesno;
				}
				//if don't want to play again
				if(yesno == 'n'){
					//go to ending page, set stopplaying to 1
					stopplaying = 1;
					endPage();
					return 0;
				}
				//if want to play again
				else if(yesno == 'y'){
					//back to the menu screen, set stopplaying to 0
					stopplaying = 0;
					return 1;
				}
			}
			//if not really want to give up
			else if(yesno == 'n'){
				//do nothing, back to the game by enter command
			}
		}
		
	//quit
		else if(command == 3){
			cout<<"Do you want to quit without save?";
			cin>>yesno2;
			while(yesno2 != 'y' && yesno2 != 'n'){
				cout<<"Please re-enter again (y/n): ";
				cin>>yesno2;
			}
			if(yesno2 == 'y'){
				stopplaying = 1;
				endPage();
				return 0;
			}
			else if(yesno2 == 'n'){
				stopplaying = 1;
				//document write and export and save
				cout<<"saving..."<<endl;
				endPage();
				return 0;
			}
		}
		
	//move	
		else if(command == 4){
			usergo = typemove();
			if(win == 1){
				boardGenerate();
				cout<<"You win!!!!"<<endl;
				
				cout<<"Do you want to play again? (y/n) ";
				cin>>yesno;
				//error check
				while(yesno != 'y' && yesno != 'n'){
					cout<<"Please enter again (y/n): ";
					cin>>yesno;
				}
				//if don't want to play again
				if(yesno == 'n'){
					//go to ending page, set stopplaying to 1
					stopplaying = 1;
					endPage();
					return 0;
				}
				//if want to play again
				else if(yesno == 'y'){
					//back to the menu screen, set stopplaying to 0
					stopplaying = 0;
					return 1;
				}
			}
			if (usergo == 0){
				pcmove();
				usergo = 1;      //if user go second, here will be  still usergo = 1 (in another part)
			}
		}
	}
	}
	
}

//get command in the main menu screen
int receiveUser(){
	string command;
	int again = 1;

	while (again == 1){
		boardGenerate();
		cout<<endl<<"Enter a command: ";
		cin>>command;
		//type help
		if(command == "help"){
			//go the help page
			return 1;
		}
		//type up
		else if(command == "up"){
			//go to give up condition
			return 2;
		}
		//type quit
		else if(command == "quit"){
			//go to end page
			return 3;
		}
		//type move
		else if(command == "move"){
			//go to typemove
			return 4;
		}
		else{
			//type again
			again = 1;
		}
	}
}

//mini help page
void miniHelp(){
	cout<<endl;
	cout<<"You can type these command: help,up,quit,move"<<endl<<endl;
	cout<<"Moves for each pieces: "<<endl;
	cout<<"King (k): one square in any direction."<<endl;
	cout<<"Root (r): move any number of squares along any rank or file, but may not leap over other pieces."<<endl;
	cout<<"Bishop (b): move any number of squares diagonally, but may not leap over other pieces."<<endl;
	cout<<"Queen (q): can move any number of squares along rank, file, or diagonal, but it may not leap over other pieces."<<endl;
	cout<<"Knight (k): moves to any of the closest squares that are not on the same rank, file, or diagonal, thus the move forms an \"L\"-shape, can leap over other pieces."<<endl;
	cout<<"Pawn (p): first move can move 1 or 2 boxes forward, after moved once, it can only move forward by 1 step."<<endl<<"Capture an opponent's piece on a square diagonally in front of it on an adjacent file, by moving to that square."<<endl;
	cout<<"If the pawn reach the opposite bound, it can change its type to queen, knight, rook, or bishop."<<endl;
	cout<<endl;
}

//board generator
void boardGenerate(){
	cout<<" ";
	for(int k =0;k<8;k++){
		cout<<" "<<word[k]<<"  ";
	}
	cout<<endl;
	cout<<" ¢z¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢s¢w¢{"<<endl;
	for(int i = 0;i<8;i++){	
		cout<<i+1<<"¢x";
		for(int j = 0;j<8;j++){
		//	cout<<"in"<<endl;
			if(board[i][j] == '1' || board[i][j] == '2' || board[i][j] == '3' || board[i][j] == '4' || board[i][j] == '5' || board[i][j] == '6' || board[i][j] == '7' || board[i][j] == '8'){
				cout<<" p"<<"¢x";
			//	cout<<"hi";
			}
			else if(board[i][j] == '!' || board[i][j] == '@' ||board[i][j] == '#' ||board[i][j] == '$' ||board[i][j] == '%' ||board[i][j] == '^' ||board[i][j] == '&' ||board[i][j] == '*' ){
				cout<<" P"<<"¢x";
			//	cout<<"2";
			}
			else{
				cout<<" "<<board[i][j]<<"¢x";
			//	cout<<"3";
			}
		}
		cout<<endl;
		cout<<"  |-------------------------------|"<<endl;
	}
}

//user enter where they want to move from _ to _
int typemove(){
	int nopiece = 1,utype = -1,typewrong = 1,movewrong,unmovable;
	string from, to;
	char tempfrom = 'z',changetype;
	
	//ask to enter from position
	while(nopiece == 1 ||typewrong == 1 || movewrong == 1 ||unmovable == 1){
		nopiece = 0;
		typewrong = 0;
		cout<<"Enter move: from position ";
		cin>>from;
		//error check
		while((from.at(0) < 97 || from.at(0) >104) || (from.at(1) < 49 || from.at(1) >56)){
			cout<<"Please enter valid position (e.g. d2): ";
			cin>>from;
		}
		
		//ask to enter to position
		cout<<"Enter move: to position ";
		cin>>to;
		//error check
		while((to.at(0) <97 || to.at(0) > 104) || (to.at(1) < 49 || to.at(1) >56) || to == from){
			cout<<"Please enter valid position (e.g. d2): ";
			cin>>to;
		}
	
		//set 'from x' and 'to x' values
		fx = from.at(1)-49;
		tx = to.at(1)-49;
		
		//change from y value
		if(from.at(0) == 'a'){
			fy = 0;
		}
		else if(from.at(0) == 'b'){
			fy = 1;
		}
		else if(from.at(0) == 'c'){
			fy = 2;
		}
		else if(from.at(0) == 'd'){
			fy = 3;
		}
		else if(from.at(0) == 'e'){
			fy = 4;
		}
		else if(from.at(0) == 'f'){
			fy = 5;
		}
		else if(from.at(0) == 'g'){
			fy = 6;
		}
		else if(from.at(0) == 'h'){
			fy = 7;
		}
		
		//change to y value
		if(to.at(0) == 'a'){
			ty = 0;
		}
		else if(to.at(0) == 'b'){
				ty = 1;
		}
		else if(to.at(0) == 'c'){
			ty = 2;
		}
		else if(to.at(0) == 'd'){
			ty = 3;
		}
		else if(to.at(0) == 'e'){
			ty = 4;
		}
		else if(to.at(0) == 'f'){
			ty = 5;
			}
		else if(to.at(0) == 'g'){
			ty = 6;
		}
		else if(to.at(0) == 'h'){
			ty = 7;
		}
			
			
		//check is there a piece to move(check from)

		nopiece = checkpresent();
		utype = checkpiecetype();
		unmovable = movable();

		//check type and go to specific type checking functions
		//wrong type
		if(utype == 999 || utype == 111){
			typewrong = 1;
			cout<<"The type is wrong."<<endl;
		}
		//king
		else if(utype == 0){
			movewrong = kingcheck();
		}
		//queen
		else if(utype == 1){
			movewrong = queencheck();
		}
		//knight
		else if(utype == 2){
			movewrong = knightcheck();
		}
		//bishop
		else if(utype == 3){
			movewrong = bishopcheck();
		}
		//rook
		else if(utype == 4){
			movewrong = rookcheck();
		}
		//pawn
		else if(utype == 5){
			movewrong = pawncheck();
		}

	}

	//move the piece by interchange the pieces
	tempfrom = board[fx][fy];
	board[tx][ty] = tempfrom;
	board[fx][fy] = '\0';
	
	//show how user moved
	cout<<"you move from "<<from<<" to "<<to<<endl;
	
	if((board[tx][ty] == '1' || board[tx][ty] == '2' || board[tx][ty] == '3' || board[tx][ty] == '4' || board[tx][ty] == '5' || board[tx][ty] == '6' || board[tx][ty] == '7' || board[tx][ty] == '8' )&&(tx == 0)){
		//tell user the pawn can promotion
		cout<<"Your pawn can change its type, please choose one of these (q,n,b,r): ";
		cin>>changetype;
		//error chec
		while(changetype != 'q' && changetype != 'n' && changetype != 'b' && changetype != 'r'){
			cout<<"Please enter a correct type: ";
			cin>>changetype;
		}
		//change type
		board[tx][ty] = changetype;
		//show board again
		boardGenerate();
	}
	
	for(int i = 0;i<8;i++){
		for(int j = 0;j<8;j++){
			if(board[i][j] == 'K'){
				win = 0;
				break;
			}
			//if pc king is not found, player win (1)
			else{
				win = 1;
			}
		}
		if(win == 0){
			break;
		}
	}
	
	//reset checking
	nopiece = 1;
	typewrong = 1;

	
	return 0;
}

//check if there are a piece on from position
int checkpresent(){
	int nopiece = 0;
	//error check, if there is no piece to move
	if(board[fx][fy] == '\0'){
		nopiece = 1;
		cout<<"There's no piece to move. Please enter again."<<endl;
		return nopiece;
	}
	return nopiece;
}

//check what is the type of the user pick to move
int checkpiecetype(){
	//set char variable
	char upiece;
	//set upiece as the name of piece
	upiece = board[fx][fy];
	
	//if king
	if(upiece == 'k'){
		return 0;
	}
	//queen
	else if(upiece == 'q'){
		return 1;
	}
	//knight
	else if(upiece == 'n'){
		return 2;
	}
	//bishop
	else if(upiece == 'b'){
		return 3;
	}
	//rooks
	else if(upiece == 'r'){
		return 4;
	}
	//pawn
	else if(upiece == '1' || upiece == '2' || upiece == '3' || upiece == '4' || upiece == '5' || upiece == '6' || upiece == '7' || upiece == '8'){
		return 5;
	}
	//pc pieces
	else if(upiece == 'K' || upiece == 'Q' || upiece == 'N' || upiece == 'B' || upiece == 'R' || upiece == '!' || upiece == '@' || upiece == '#' || upiece == '$' || upiece == '%' || upiece == '^' || upiece == '&' || upiece == '*' ){
		return 999;
	}
	//other unexpected
	else{
		return 111;
	}
	
	
}


//check user pawn
int pawncheck(){
	int movewrong = 1;
	
	//killing condition
	//if going cross by 1
	if(abs(fy-ty) == 1 && fx-tx == 1){
		//if it is pc pawn
		if(board[tx][ty] == 'K' || board[tx][ty] == 'Q' || board[tx][ty] == 'N' || board[tx][ty] == 'B' || board[tx][ty] == 'R' || board[tx][ty] == '!' || board[tx][ty] == '@' || board[tx][ty] == '#' || board[tx][ty] == '$' || board[tx][ty] == '%' || board[tx][ty] == '^' || board[tx][ty] == '&' || board[tx][ty] == '*'){
			movewrong = 0;
			return movewrong;
		}
		return movewrong;
	}
	
	//first move
	if(pawnmoved[(int)(board[fx][fy]-48)] == false ){
		//if it is user pawn
		if((int)board[fx][fy]-48 == 1 || (int)board[fx][fy]-48 == 2 || (int)board[fx][fy]-48 == 3 || (int)board[fx][fy]-48 == 4 || (int)board[fx][fy]-48 == 5 || (int)board[fx][fy]-48 == 6 || (int)board[fx][fy]-48 == 7 || (int)board[fx][fy]-48 == 8){
			//move forward and move less than or equal to 2 and more than 0 and move forward
			if(fx>tx && fx-tx <= 2 && fx-tx > 0 && fy-ty == 0){
				if(board[tx][ty] != 'K' && board[tx][ty] != 'Q' && board[tx][ty] != 'N' && board[tx][ty] != 'B' && board[tx][ty] != 'R' && board[tx][ty] != '!' && board[tx][ty] != '@' && board[tx][ty] != '#' && board[tx][ty] != '$' && board[tx][ty] != '%' && board[tx][ty] != '^' && board[tx][ty] != '&' && board[tx][ty] != '*')
					movewrong = 0;
					//set flag to true
					pawnmoved[(int)board[fx][fy]-48] = true;
					return movewrong;
			}
			return movewrong;
		}
		return movewrong;
	}
	else{
		//if it is user pawn
		if((int)board[fx][fy]-48 == 1 || (int)board[fx][fy]-48 == 2 || (int)board[fx][fy]-48 == 3 || (int)board[fx][fy]-48 == 4 || (int)board[fx][fy]-48 == 5 || (int)board[fx][fy]-48 == 6 || (int)board[fx][fy]-48 == 7 || (int)board[fx][fy]-48 == 8){
			//move forward and move more than 0 and move less than 2 and move forward
			if(fx>tx && fx-tx > 0 && fx-tx<2 && fy-ty == 0){
					if(board[tx][ty] != 'K' && board[tx][ty] != 'Q' && board[tx][ty] != 'N' && board[tx][ty] != 'B' && board[tx][ty] != 'R' && board[tx][ty] != '!' && board[tx][ty] != '@' && board[tx][ty] != '#' && board[tx][ty] != '$' && board[tx][ty] != '%' && board[tx][ty] != '^' && board[tx][ty] != '&' && board[tx][ty] != '*'){
						movewrong = 0;
						return movewrong;
					}
			}
			return movewrong;
		}
		return movewrong;
	}
}


//check user rook
int rookcheck(){
	int movewrong = 0;
	if(fx != tx && fy != ty){
		movewrong = 1;
		return movewrong;
	}
	//move down to up
	else if(fx>tx){
		for(int i = fx-1;i>tx;i--){
			if(board[i][fy] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//move up to down
	else if(fx<tx){
		for(int i = fx+1;i<tx;i++){
			if(board[i][fy] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//move right to left
	else if(fy>ty){
		for(int i = fy-1;i>ty;i--){
			if(board[fx][i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//move left to right
	else if(fy<ty){
		for(int i = fy+1;i<ty;i++){
			if(board[fx][i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	return movewrong;
}

//check user bishop
int bishopcheck(){
	int movewrong = 0,diff = 0;
	if(fx == tx || fy == ty){
		movewrong = 1;
		return movewrong;
	}
	//right upper corner
	else if(fx>tx && fy<ty){
		diff = fx-tx;
		for(int i = 1;i<diff;i++){
			if(board[fx-i][fy+i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//right lower corner
	else if(fx<tx && fy<ty){
		diff = tx-fx;
		for(int i = 1;i<diff;i++){
			if(board[fx+i][fy+i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//left upper corner
	else if(fx>tx && fy>ty){
		diff = fx-tx;
		for(int i = 1;i<diff;i++){
			if(board[fx-i][fy-i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	//left lower corner
	else if(fx<tx && fy>ty){
		diff = tx-fx;
		for(int i = 1;i<diff;i++){
			if(board[fx+i][fy-i] != '\0'){
				movewrong = 1;
				return movewrong;
			}
		}
	}
	return movewrong;
}

//check user knight
int knightcheck(){
	int movewrong = 1;
	if(fx == tx || fy == ty){
		movewrong = 1;
		return movewrong;
	}
	//up
	if(fx == tx+2 && (fy == ty-1 || fy == ty+1)){
		movewrong = 0;
		return movewrong;
	}
	//down
	else if(fx == tx-2 && (fy == ty-1 || fy == ty+1)){
		movewrong = 0;
		return movewrong;
	}
	//left
	else if(fy == ty+2 && (fx == tx-1 || fx == tx+1)){
		movewrong = 0;
		return movewrong;
	}
	//right
	else if(fy == ty-2 && (fx == tx-1 || fx == tx+1)){
		movewrong = 0;
		return movewrong;
	}
	return movewrong;
}

//check user queen
int queencheck(){
	int movewrong = 0,diff;
	
	//bishop case
	if(abs(fx-tx) == abs(fy-ty)){
	//right upper corner
		if(fx>tx && fy<ty){
			diff = fx-tx;
			for(int i = 1;i<diff;i++){
				if(board[fx-i][fy+i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//right lower corner
		else if(fx<tx && fy<ty){
			diff = tx-fx;
			for(int i = 1;i<diff;i++){
				if(board[fx+i][fy+i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//left upper corner
		else if(fx>tx && fy>ty){
			diff = fx-tx;
			for(int i = 1;i<diff;i++){
				if(board[fx-i][fy-i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//left lower corner
		else if(fx<tx && fy>ty){
			diff = tx-fx;
			for(int i = 1;i<diff;i++){
				if(board[fx+i][fy-i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		return movewrong;
	}
	
	
	//rook case
	//move down to up
	else if(fx-tx == 0 || fy-ty == 0){
		if(fx>tx){
			for(int i = fx-1;i>tx;i--){
				if(board[i][fy] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//move up to down
		else if(fx<tx){
			for(int i = fx+1;i<tx;i++){
				if(board[i][fy] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//move right to left
		else if(fy>ty){
			for(int i = fy-1;i>ty;i--){
				if(board[fx][i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		//move left to right
		else if(fy<ty){
			for(int i = fy+1;i<ty;i++){
				if(board[fx][i] != '\0'){
					movewrong = 1;
					return movewrong;
				}
			}
		}
		return movewrong;
	}
	//if not in the above 2 cases
	else{
		movewrong = 1;
		return movewrong;
	}	
}

//check user king (without killing)
int kingcheck(){
	int movewrong = 1;
	//if in these condition
	if((abs(fx-tx) == 1 || abs(fx-tx) == 0) && (abs(fy-ty) == 1 || abs(fy-ty) == 0)){
		//right steps
		movewrong = 0;
		return movewrong;
	}
	//else wrong steps
	return movewrong;
}


//check user pieces, not killing users pieces
int movable(){
	int unmovable = 0;
	//if 'to' is have these elements which are user pieces
	if (board[tx][ty] == '1' || board[tx][ty] == '2' || board[tx][ty] == '3' || board[tx][ty] == '4' || board[tx][ty] == '5' || board[tx][ty] == '6' || board[tx][ty] == '7' || board[tx][ty] == '8' || board[tx][ty] == 'k' || board[tx][ty] == 'q' || board[tx][ty] == 'n' || board[tx][ty] == 'b' || board[tx][ty] == 'r'){
		//not movable
		unmovable = 1;
		return unmovable;
	}
	//else movable
	else{
		return unmovable;
	}
}




//----pc------------------------------------------------pc-------------------------------------pc---------------------------------------pc----------------------------

int pcmove(){
       	//movable();   need to change sth in this function
    int summ = 0;
    bool notmove = 0;
    char tempfrom;
    //set flag that the move is wrong when it is 1
	int movewrong = 1;
	//set flag that 'pc from' need to random again when it is 1
	int frandagain = 1;
	srand(time(0));
	
	while(frandagain == 1 || notmove == 1){
		notmove = 0;
		frandagain = 1;
//		frandagain = 1;
		//random value for 'pc from' walue
			pfx = rand()%8;
			pfy = rand()%8;
			
			
	//if pc piece is chosen
		if((board[pfx][pfy] == 'R' || board[pfx][pfy] == 'N' || board[pfx][pfy] == 'B' || board[pfx][pfy] == 'Q' || board[pfx][pfy] == 'K' || board[pfx][pfy] == '!' || board[pfx][pfy] == '@' || board[pfx][pfy] == '#' || board[pfx][pfy] == '$' || board[pfx][pfy] == '%' || board[pfx][pfy] == '^' || board[pfx][pfy] == '&' || board[pfx][pfy] == '*')){
			frandagain = 0;
			
			//if it is rook
			if(board[pfx][pfy] == 'R'){
				
				
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				if(notmove == 0){
					
					random_moves();
					
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
					
				}
				
			}
			
			//if it is knight
			else if(board[pfx][pfy] == 'N'){
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				if(notmove == 0){
					
					random_moves();
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
					
				}	
			}
			
			//if it is bishop
			else if(board[pfx][pfy] == 'B'){
				
				//check moves
				
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				if(notmove == 0){
					
					random_moves();
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
					
				}
			}
			
			//if it is Queen
			else if(board[pfx][pfy] == 'Q'){
				
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				//if there are moves
				if(notmove == 0){
					
					//go get random number to retrive 'to' values
					random_moves();  //see if it can be used as the same function
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
				}
			}
			
			//if it is King
			else if(board[pfx][pfy] == 'K'){
				
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				//if there are moves
				if(notmove == 0){
					
					//go get random number to retrive 'to' values
					king_random_moves();  //see if it can be used as the same function
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
				}
			}
			
			//if it is pawn
			else{
				
				notmove = possiblemove(board[pfx][pfy]);  //return 0 if there are moves, return 1 if there are no moves
				
				if(notmove == 0){
					
					random_moves();  //see if it can be used as the same function
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
				}
				else if(notmove == 3){
					
					//exchange the value between from and to value
					tempfrom = board[pfx][pfy];
					board[ptx][pty] = tempfrom;
					board[pfx][pfy] = '\0';
					
					//if reach user's boarder, it changes to queen type
					if(ptx == 7){
						board[ptx][pty] = 'q';
					}
					
				}
			}
			
		}
	
		
	}
	
		for(int i = 0;i<8;i++){
			for(int j = 0;j<8;j++){
				//if user king is found
				if(board[i][j] == 'k'){
					win = 0;
					break;
				}
				//IF NOT
				//if user king is not found, pc win (2)
				else{
					win = 2;
				}
			}
			//if not win
			if(win == 0){
				break;
			}
		}
		
}


//check pc knight (get the moves randomly)
void pcknightcheck(){
	int cases,cases2,movewrong = 1;
	srand(time(0));
	//while movewrong
	while(movewrong == 1){
		//random generate number for 2 cases variables
		cases = rand()%4;
		cases2 = rand()%2;
		
		//up
		if(cases == 0){
			if(pfx-2 >= 0){
				//right
				if(cases2 == 0 && pfy+1 <= 7){
					movewrong = 0;
					ptx = pfx-2;
					pty = pfy+1;
				}
				//left
				else if(cases2 == 1 && pfy-1 >= 0){
					movewrong = 0;
					ptx = pfx-2;
					pty = pfy-1;
				}
			}
			//out of bound
			else{
				movewrong = 1;
			}
		}
		//down
		else if(cases == 1){
			if(pfx+2 <= 7){
				//right
				if(cases2 == 0 && pfy+1 <= 7){
					movewrong = 0;
					ptx = pfx+2;
					pty = pfy+1;
				}
				//left
				else if(cases2 == 1 && pfy-1 >= 0){
					movewrong = 0;
					ptx = pfx+2;
					pty = pfy-1;
				}
			}
			//out of bound
			else{
				movewrong = 1;
			}
		}
		//left
		else if(cases == 2){
			if(pfy-2 >= 0){
				//down
				if(cases2 == 0 && pfx+1 <= 7){
					movewrong = 0;
					ptx = pfx+1;
					pty = pfy-2;
				}
				//up
				else if(cases2 == 1 && pfx-1 >= 0){
					movewrong = 0;
					ptx = pfx-1;
					pty = pfy-2;
				}
			}
			//out of bound
			else{
				movewrong = 1;
			}
		}
		//right
		else if(cases == 3){
			if(pfy+2 <= 7){
				//down
				if(cases2 == 0 && pfx+1 <= 7){
					movewrong = 0;
					pty = pfy+2;
					ptx = pfx+1;
				}
				//up
				else if(cases2 == 1 && pfx-1 >= 0){
					movewrong = 0;
					pty = pfy+2;
					ptx = pfx-1;
				}
			}
			//out of bound
			else{
				movewrong = 1;
			}
		}
		
		//set movewrong from getting the values from pcmovable function
		movewrong = pcmovable();
	}
	
}

//check pc bishop (get the moves randomly)
int random_moves(){
	int movewrong = 1,diff,sum = 0;
	int cases;
	srand(time(0));
	//random number for cases
	cases = rand()%35;
	//while the array in pomoves1 and pomoves2 in plaes 'cases' both = -1
	while(pomoves1[cases] == -1 && pomoves2[cases] == -1){
		//random generate number
		cases = rand()%35;
	}
	//set ptx and pty
	ptx = pomoves1[cases];
	pty = pomoves2[cases];
}

int king_random_moves(){
	int movewrong = 1,diff,sum = 0;
	int cases;
	srand(time(0));
	//random number for cases
	cases = rand()%8;
	//while the array in pomoves1 and pomoves2 in plaes 'cases' both = -1
	while(king1[cases] == -1 && king2[cases] == -1){
		//random generate number
		cases = rand()%8;
	}
	//set ptx and pty
	ptx = king1[cases];
	pty = king2[cases];
}


//check and find all the possible moves
int possiblemove(char type){
	//set variables
	int stopone = 0,stoptwo = 0,stopthree = 0,stopfour = 0,stopfive = 0,stopsix = 0,stopseven = 0,stopeight = 0;
	int allneg = 1;
	//reset all the values in the array to -1
	for(int i =0;i<35;i++){
		pomoves1[i] = -1;
		pomoves2[i] = -1;
	}
	for(int i = 0;i<8;i++){
		king1[i] = -1;
		king2[i] = -1;
	}
	int a = 0;
	
				/*	      1  2
						3      4
							K
						5      6
	//check knight		  7  8    */
	if(type == 'N'){ 
		//pos 1
		if(board[pfx-2][pfy-1] == '\0' && pfx-2 >=0 && pfy-1 >=0){
			pomoves1[a] = pfx-2;
			pomoves2[a] = pfy-1;
			a++;
		}
		//pos 2
		if(board[pfx-2][pfy+1] == '\0' && pfx-2 >=0 && pfy+1 <8){
			pomoves1[a] = pfx-2;
			pomoves2[a] = pfy+1;
			a++;
		}
		
		//pos 3
		if(board[pfx-1][pfy-2] == '\0' && pfx-1 >=0 && pfy-2 >=0){
			pomoves1[a] = pfx-1;
			pomoves2[a] = pfy-2;
			a++;
		}
		//pos 4
		if(board[pfx-1][pfy+2] == '\0' && pfx-1 >=0 && pfy+2 <8){
			pomoves1[a] = pfx-1;
			pomoves2[a] = pfy+2;
			a++;
		}
		
		//pos 5
		if(board[pfx+1][pfy-2] == '\0' && pfx+1 <8 && pfy-2 >=0){
			pomoves1[a] = pfx+1;
			pomoves2[a] = pfy-2;
			a++;
		}
		//pos 6
		if(board[pfx+1][pfy+2] == '\0' && pfx+1 <8 && pfy+2 <8){
			pomoves1[a] = pfx+1;
			pomoves2[a] = pfy+2;
			a++;
		}
		
		//pos 7
		if(board[pfx+2][pfy-1] == '\0' && pfx+2 <8 && pfy-1 >=0){
			pomoves1[a] = pfx+2;
			pomoves2[a] = pfy-1;
			a++;
		}
		//pos 8
		if(board[pfx+2][pfy+1] == '\0' && pfx+2 <8 && pfy+1 <8){
			pomoves1[a] = pfx+2;
			pomoves2[a] = pfy+1;
			a++;	
		}
		
	}
	
	
	
	//check bishop
	if(type == 'B'){
		for(int i = 1;i<8;i++){
			//right down
			if(board[pfx+i][pfy+i] == '\0' && pfx+i <8 && pfy+i <8 && stopone == 0){
				
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy+i;
				a++;
			}
			else{
				stopone = 1;
			}
			//left down
			if(board[pfx+i][pfy-i] == '\0' && pfx+i <8 && pfy-i >=0 && stoptwo == 0){
			
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy-i;
				a++;	
			}
			else{
				stoptwo = 1;
			}
			//left up
			if(board[pfx-i][pfy-i] == '\0' && pfx-i >=0 && pfy-i >=0 && stopthree == 0){
	
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy-i;	
				a++;
			}
			else{
				stopthree = 1;
			}
			//right up
			if(board[pfx-i][pfy+i] == '\0' && pfx-i >=0 && pfy+i <8 && stopfour == 0){
				
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy+i;
				a++;	
			}
			else{
				stopfour = 1;
			}
		}
		
	}
	
	//check rook
	else if(type == 'R'){
		for(int i = 1;i<8;i++){
			//vertical
			if(board[pfx+i][pfy] =='\0' && pfx+i < 8 && stopone == 0){
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy;
				a++;
			}
			else{
				stopone = 1;
			}
			
			if(board[pfx-i][pfy] =='\0' && pfx-i >= 0 && stoptwo == 0){
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy;
				a++;
			}
			else{
				stoptwo = 1;
			}
			
			//horizontal
			if(board[pfx][pfy-i] =='\0' && pfy-i >= 0 && stopthree == 0){
				pomoves1[a] = pfx;
				pomoves2[a] = pfy-i;
				a++;
			}
			else{
				stopthree = 1;
			}
			
			if(board[pfx][pfy+i] =='\0' && pfy+i < 8 && stopfour == 0){
				pomoves1[a] = pfx;
				pomoves2[a] = pfy+i;
				a++;
			}
			else{
				stopfour = 1;
			}
		}
		
		for(int i = 0;i<35;i++){
			if(pomoves1[i] != -1 && pomoves2[i] != -1){
				return 0;
			}
		}
	}
	
	//check queen
	else if(type == 'Q'){
		for(int i = 1;i<8;i++){
			//vertical up
			if(board[pfx+i][pfy] =='\0' && pfx+i < 8 && stopone == 0){
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy;
				a++;
			}
			else{
				stopone = 1;
			}
			//vertical down
			if(board[pfx-i][pfy] =='\0' && pfx-i >= 0 && stoptwo == 0){
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy;
				a++;
			}
			else{
				stoptwo = 1;
			}
			
			//horizontal left
			if(board[pfx][pfy-i] =='\0' && pfy-i >= 0 && stopthree == 0){
				pomoves1[a] = pfx;
				pomoves2[a] = pfy-i;
				a++;
			}
			else{
				stopthree = 1;
			}
			//horizontal right
			if(board[pfx][pfy+i] =='\0' && pfy+i < 8 && stopfour == 0){
				pomoves1[a] = pfx;
				pomoves2[a] = pfy+i;
				a++;
			}
			else{
				stopfour = 1;
			}
			
			//cross moves
			//right down
			if(board[pfx+i][pfy+i] == '\0' && pfx+i <8 && pfy+i <8 && stopfive == 0){
				
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy+i;
				a++;
			}
			else{
				stopfive = 1;
			}
			//left down
			if(board[pfx+i][pfy-i] == '\0' && pfx+i <8 && pfy-i >=0 && stopsix == 0){
			
				pomoves1[a] = pfx+i;
				pomoves2[a] = pfy-i;
				a++;	
			}
			else{
				stopsix = 1;
			}
			//left up
			if(board[pfx-i][pfy-i] == '\0' && pfx-i >=0 && pfy-i >=0 && stopseven == 0){
	
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy-i;	
				a++;
			}
			else{
				stopseven = 1;
			}
			//right up
			if(board[pfx-i][pfy+i] == '\0' && pfx-i >=0 && pfy+i <8 && stopeight == 0){
				
				pomoves1[a] = pfx-i;
				pomoves2[a] = pfy+i;
				a++;	
			}
			else{
				stopeight = 1;
			}
		}
	}
	
	//check pawn
	else if(type == '!' || type == '@' || type == '#' || type == '$' || type == '%' || type == '^' || type == '&' || type == '*'){
		type = pawnnum(type);
		//if it is pawn first move
		if(pcpawnmoved[type] == false){
			//front 1
			if(pfx+1 < 8 && board[pfx+1][pfy] == '\0'){
				pomoves1[0] = pfx+1;
				pomoves2[0] = pfy;
			}
			//front 2
			if(pfx+2 < 8 && board[pfx+2][pfy] == '\0' && board[pfx+1][pfy] == '\0'){
				pomoves1[1] = pfx+2;
				pomoves2[1] = pfy;
			}
			//front left
			if(pfx+1 < 8 && pfy-1 >= 0 && (board[pfx+1][pfy-1] == '1' || board[pfx+1][pfy-1] == '2' || board[pfx+1][pfy-1] == '3' || board[pfx+1][pfy-1] == '4' || board[pfx+1][pfy-1] == '5' || board[pfx+1][pfy-1] == '6' || board[pfx+1][pfy-1] == '7' || board[pfx+1][pfy-1] == '8' || board[pfx+1][pfy-1] == 'r' || board[pfx+1][pfy-1] == 'n' || board[pfx+1][pfy-1] == 'b' || board[pfx+1][pfy-1] == 'q' || board[pfx+1][pfy-1] == 'k' || board[pfx+1][pfy-1] == 'b' || board[pfx+1][pfy-1] == 'n' || board[pfx+1][pfy-1] == 'r')){
				pomoves1[2] = pfx+1;
				pomoves2[2] = pfy-1;
			}
			//front right
			if(pfx+1 < 8 && pfy+1 < 8 && (board[pfx+1][pfy+1] == '1' || board[pfx+1][pfy+1] == '2' || board[pfx+1][pfy+1] == '3' || board[pfx+1][pfy+1] == '4' || board[pfx+1][pfy+1] == '5' || board[pfx+1][pfy+1] == '6' || board[pfx+1][pfy+1] == '7' || board[pfx+1][pfy+1] == '8' || board[pfx+1][pfy+1] == 'r' || board[pfx+1][pfy+1] == 'n' || board[pfx+1][pfy+1] == 'b' || board[pfx+1][pfy+1] == 'q' || board[pfx+1][pfy+1] == 'k' || board[pfx+1][pfy+1] == 'b' || board[pfx+1][pfy+1] == 'n' || board[pfx+1][pfy+1] == 'r')){
				pomoves1[3] = pfx+1;
				pomoves2[3] = pfy+1;
			}
			pcpawnmoved[type] = true;
		}
		
		//if it is not pawn first move
		else{
			//front
			if(pfx+1 < 8 && board[pfx+1][pfy] == '\0'){
				pomoves1[0] = pfx+1;
				pomoves2[0] = pfy;
			}
			//front left
			if(pfx+1 < 8 && pfy-1 >= 0 && (board[pfx+1][pfy-1] == '1' || board[pfx+1][pfy-1] == '2' || board[pfx+1][pfy-1] == '3' || board[pfx+1][pfy-1] == '4' || board[pfx+1][pfy-1] == '5' || board[pfx+1][pfy-1] == '6' || board[pfx+1][pfy-1] == '7' || board[pfx+1][pfy-1] == '8' || board[pfx+1][pfy-1] == 'r' || board[pfx+1][pfy-1] == 'n' || board[pfx+1][pfy-1] == 'b' || board[pfx+1][pfy-1] == 'q' || board[pfx+1][pfy-1] == 'k' || board[pfx+1][pfy-1] == 'b' || board[pfx+1][pfy-1] == 'n' || board[pfx+1][pfy-1] == 'r')){
				pomoves1[1] = pfx+1;
				pomoves2[1] = pfy-1;
			}
			//front right
			if(pfx+1 < 8 && pfy+1 < 8 && (board[pfx+1][pfy+1] == '1' || board[pfx+1][pfy+1] == '2' || board[pfx+1][pfy+1] == '3' || board[pfx+1][pfy+1] == '4' || board[pfx+1][pfy+1] == '5' || board[pfx+1][pfy+1] == '6' || board[pfx+1][pfy+1] == '7' || board[pfx+1][pfy+1] == '8' || board[pfx+1][pfy+1] == 'r' || board[pfx+1][pfy+1] == 'n' || board[pfx+1][pfy+1] == 'b' || board[pfx+1][pfy+1] == 'q' || board[pfx+1][pfy+1] == 'k' || board[pfx+1][pfy+1] == 'b' || board[pfx+1][pfy+1] == 'n' || board[pfx+1][pfy+1] == 'r')){
				pomoves1[2] = pfx+1;
				pomoves2[2] = pfy+1;
			}
		}
	}
	
	//if it is king
	else if(type == 'K'){	/*	1 2 3
								4 K 5
								6 7 8	*/
		//position 1
		if(board[pfx-1][pfy-1] == '\0' && pfx-1 >= 0 && pfy-1 >= 0){
			king1[a] = pfx-1;
			king2[a] = pfy-1;
			a++;
		}
		//position 2
		if(board[pfx-1][pfy] == '\0' && pfx-1 >= 0){
			king1[a] = pfx-1;
			king2[a] = pfy;
			a++;
		}
		//position 3
		if(board[pfx-1][pfy+1] == '\0' && pfx-1 >= 0 && pfy+1 < 8){
			king1[a] = pfx-1;
			king2[a] = pfy+1;
			a++;
		}
		//position 4
		if(board[pfx][pfy-1] == '\0' && pfy-1 >= 0){
			king1[a] = pfx;
			king2[a] = pfy-1;
			a++;
		}
		//position 5
		if(board[pfx][pfy+1] == '\0' && pfy+1 < 8){
			king1[a] = pfx;
			king2[a] = pfy+1;
			a++;
		}
		//position 6
		if(board[pfx+1][pfy-1] == '\0' && pfx+1 < 8 && pfy-1 >= 0){
			king1[a] = pfx+1;
			king2[a] = pfy-1;
			a++;
		}
		//position 7
		if(board[pfx+1][pfy] == '\0' && pfx+1 < 8 ){
			king1[a] = pfx+1;
			king2[a] = pfy;
			a++;
		}
		//position 8
		if(board[pfx+1][pfy+1] == '\0' && pfx+1 < 8 && pfy+1 < 8){
			king1[a] = pfx+1;
			king2[a] = pfy+1;
			a++;
		}
		
		
		//check once before searching, reduce time
		for(int i = 0;i<8;i++){
			if(king1[i] != -1 && king2[i] != -1){
				allneg = 0;
			}
		}
		if(allneg == 1){
			return 1;
		}
		
		//search is there any move are not allow because other pieces can step on it later
		search();
		
		//check have possible moves or not
		for(int i = 0;i<8;i++){
			if(king1[i] != -1 && king2[i] != -1){
				return 0;
			}
		}	
		
		return 1;
			
	}
	
		//check is there any possible moves
		for(int i = 0;i<35;i++){
			if(pomoves1[i] != -1 && pomoves2[i] != -1){
				return 0;
			}
		}
}

//search for king that cant step on it
int search(){
	//set variables
	int stopone = 0,stoptwo = 0,stopthree = 0,stopfour = 0,stopfive = 0,stopsix = 0,stopseven = 0,stopeight = 0;
	//reset all the values in the array to -1
	for(int i =0;i<35;i++){
		pomoves1[i] = -1;
		pomoves2[i] = -1;
	}
	int a = 0;
	
	//loop the whole board find pieces
	for(int j = 0;j<8;j++){
		for(int k = 0;k<8;k++){
			stopone = 0,stoptwo = 0,stopthree = 0,stopfour = 0,stopfive = 0,stopsix = 0,stopseven = 0,stopeight = 0;
			a = 0;
			
			//if type user rook
			if(board[j][k] == 'r'){
				
				//loop the difference of the possible moves
				for(int i = 1;i<8;i++){
				//vertical
					if(board[j+i][k] =='\0' && j+i < 8 && stopone == 0){
						pomoves1[a] = j+i;
						pomoves2[a] = k;
						a++;
					}
					else{
						stopone = 1;
					}
			
					if(board[j-i][k] =='\0' && j-i >= 0 && stoptwo == 0){
						pomoves1[a] = j-i;
						pomoves2[a] = k;
						a++;
					}
					else{
						stoptwo = 1;
					}
					
					//horizontal
					if(board[j][k-i] =='\0' && k-i >= 0 && stopthree == 0){
						pomoves1[a] = j;
						pomoves2[a] = k-i;
						a++;
					}
					else{
						stopthree = 1;
					}
					
					if(board[j][k+i] =='\0' && k+i < 8 && stopfour == 0){
						pomoves1[a] = j;
						pomoves2[a] = k+i;
						a++;
					}
					else{
						stopfour = 1;
					}	
				}	
			}
			
			//if type is bishop
			else if(board[j][k] == 'b'){
				//loop diff of possible moves
				for(int i = 1;i<8;i++){
					if(board[j+i][k+i] == '\0' && j+i <8 && k+i <8 && stopone == 0){
				
						pomoves1[a] = j+i;
						pomoves2[a] = k+i;
						a++;
					}
					else{
						stopone = 1;
					}
					if(board[j+i][k-i] == '\0' && j+i <8 && k-i >=0 && stoptwo == 0){
			
						pomoves1[a] = j+i;
						pomoves2[a] = k-i;
						a++;	
					}
					else{
						stoptwo = 1;
					}
			
					if(board[j-i][k-i] == '\0' && j-i >=0 && k-i >=0 && stopthree == 0){
	
						pomoves1[a] = j-i;
						pomoves2[a] = k-i;	
						a++;
					}
					else{
						stopthree = 1;
					}
			
					if(board[j-i][k+i] == '\0' && j-i >=0 && k+i <8 && stopfour == 0){
				
						pomoves1[a] = j-i;
						pomoves2[a] = k+i;
						a++;	
					}
					else{
						stopfour = 1;
					}
				}
			}
			
			//if type is queen
			else if(board[j][k] == 'q'){
				for(int i = 1;i<8;i++){
				//vertical up
					if(board[j+i][k] =='\0' && j+i < 8 && stopone == 0){
						pomoves1[a] = j+i;
						pomoves2[a] = k;
						a++;
					}
					else{
						stopone = 1;
					}
					//vertical down
					if(board[j-i][k] =='\0' && j-i >= 0 && stoptwo == 0){
						pomoves1[a] = j-i;
						pomoves2[a] = k;
						a++;
					}
					else{
						stoptwo = 1;
					}
				
					//horizontal left
					if(board[j][k-i] =='\0' && k-i >= 0 && stopthree == 0){
						pomoves1[a] = j;
						pomoves2[a] = k-i;
						a++;
					}
					else{
						stopthree = 1;
					}
					//horizontal right
					if(board[j][k+i] =='\0' && k+i < 8 && stopfour == 0){
						pomoves1[a] = j;
						pomoves2[a] = k+i;
						a++;
					}
					else{
						stopfour = 1;
					}
				
					//cross moves
					//right down
					if(board[j+i][k+i] == '\0' && j+i <8 && k+i <8 && stopfive == 0){
					
						pomoves1[a] = j+i;
						pomoves2[a] = k+i;
						a++;
					}
					else{
						stopfive = 1;
					}
					//left down
					if(board[j+i][k-i] == '\0' && j+i <8 && k-i >=0 && stopsix == 0){
					
						pomoves1[a] = j+i;
						pomoves2[a] = k-i;
						a++;	
					}
					else{
						stopsix = 1;
					}
					//left up
					if(board[j-i][k-i] == '\0' && j-i >=0 && k-i >=0 && stopseven == 0){
		
						pomoves1[a] = j-i;
						pomoves2[a] = k-i;	
						a++;
					}
					else{
						stopseven = 1;
					}
					//right up
					if(board[j-i][k+i] == '\0' && j-i >=0 && k+i <8 && stopeight == 0){
					
						pomoves1[a] = j-i;
						pomoves2[a] = k+i;
						a++;	
					}
					else{
						stopeight = 1;
					}
				}
			}
			
			//if type is king
			else if(board[j][k] == 'k'){
				if(board[j-1][k-1] == '\0' && j-1 >= 0 && k-1 >= 0){
					pomoves1[0] = j-1;
					pomoves2[0] = k-1;
				}
				//position 2
				if(board[j-1][k] == '\0' && j-1 >= 0){
					pomoves1[1] = j-1;
					pomoves2[1] = k;
				}
				//position 3
				if(board[j-1][k+1] == '\0' && j-1 >= 0 && k+1 < 8){
					pomoves1[2] = j-1;
					pomoves2[2] = k+1;
				}
				//position 4
				if(board[j][k-1] == '\0' && k-1 >= 0){
					pomoves1[3] = j;
					pomoves2[3] = k-1;
				}
				//position 5
				if(board[j][k+1] == '\0' && k+1 < 8){
					pomoves1[4] = j;
					pomoves2[4] = k+1;
				}
				//position 6
				if(board[j+1][k-1] == '\0' && j+1 < 8 && k-1 >= 0){
					pomoves1[5] = j+1;
					pomoves2[5] = k-1;
				}
				//position 7
				if(board[j+1][k] == '\0' && j+1 < 8 ){
					pomoves1[6] = j+1;
					pomoves2[6] = k;
				}
				//position 8
				if(board[j+1][k+1] == '\0' && j+1 < 8 && k+1 < 8){
					pomoves1[7] = j+1;
					pomoves2[7] = k+1;
				}
			}
			
			//if it is user pawn
			else if(board[j][k] == '1' || board[j][k] == '2' || board[j][k] == '3' || board[j][k] == '4' || board[j][k] == '5' || board[j][k] == '6' || board[j][k] == '7' || board[j][k] == '8'){
				int type = (int)board[j][k]-49;
				//if it is pawn first move
				if(pawnmoved[type] == false){
						//front left
						if(board[j-1][k-1] == '\0'){
							pomoves1[a] = j-1;
							pomoves2[a] = k-1;
							a++;
						}
						if(board[j-1][k+1] == '\0'){
							pomoves1[a] = j-1;
							pomoves2[a] = k+1;
							a++;
						}
						if(board[j-1][k] == '\0'){
							pomoves1[a] = j-1;
							pomoves2[a] = k;
							a++;
						}
						if(board[j-2][k] == '\0' && board[j-1][k] == '\0'){
							pomoves1[a] = j-2;
							pomoves2[a] = k;
							a++;
						}
				}
						
				//correct condition
				else{
					if(board[j-1][k-1] == '\0'){
						pomoves1[a] = j-1;
						pomoves2[a] = k-1;
						a++;
					}
					if(board[j-1][k+1] == '\0'){
						pomoves1[a] = j-1;
						pomoves2[a] = k+1;
						a++;
					}
					if(board[j-1][k] == '\0'){
						pomoves1[a] = j-1;
						pomoves2[a] = k;
						a++;
					}
				}	
			}
			
			//compare to see is there same movable position with rook
			for(int x = 0;x<8;x++){
				for(int y = 0;y<35;y++){
					if(king1[x] == pomoves1[y] && king2[x] == pomoves2[y]){
						king1[x] = -1;
						king2[x] = -1;
					}
				}
			}
			
		}	
	}
			
			
			
}



//get numbers to pc pawn
int pawnnum(char type){
	if (type == '!'){
		return 0;
	}
	else if (type == '@'){
		return 1;
	}
	else if (type == '#'){
		return 2;
	}
	else if (type == '$'){
		return 3;
	}
	else if (type == '%'){
		return 4;
	}
	else if (type == '^'){
		return 5;
	}
	else if (type == '&'){
		return 6;
	}
	else if (type == '*'){
		return 7;
	}
}



//not allow to step on these pc piece
int pcmovable(){
	int movewrong = 0;
	//if it is pc piece
	if(board[ptx][pty] == 'R' || board[ptx][pty] == 'N' || board[ptx][pty] == 'B' || board[ptx][pty] == 'Q' || board[ptx][pty] == 'K' || board[ptx][pty] == '!' || board[ptx][pty] == '@' || board[ptx][pty] == '#' || board[ptx][pty] == '$' || board[ptx][pty] == '%' || board[ptx][pty] == '^' || board[ptx][pty] == '&' || board[ptx][pty] == '*'){
			movewrong = 1;
			return movewrong;
	}
	//if not pc piece
	else{
		return movewrong;
	}
}

