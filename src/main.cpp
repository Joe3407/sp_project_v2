#include <iostream>
#include <fstream>
#include <string> 
#include <conio.h>  // for password 
#include <iomanip>  // for function "setw"
#include <limits>   // for user input more than the amount needed
#include <cctype>   // for tolower 
#include <algorithm> // for swap
#include <ctime>   // Necessary for time()
#include <cstdlib> // Necessary for rand() and srand()
using namespace std;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Ibrahim :

// Declaring Structs and Variables 
struct User{
    string username;
    string password;
    string role;

};
struct Team{
    string name;
    string coach ;
    int totalPoints;
    int titles;
};
struct Match {
    string team1;
    string team2;
    string date;   
    string status; 
    string time;
    int score1;   
    int score2;    
};
struct Follow{
    string username;
    string teamName;
};
User users[100];
int usersCount = 0;
Team teams[20]; 
int teamsCount = 0;
Match matches[200];
int matchesCount = 0;
Follow follow[200];
int followCount = 0 ;
string currentLoggedInUser = "";
string currentUserRole = "";

// Defining Functions 
void SaveData(){
    // Saving Teams 
    ofstream teamFile("teams.txt");
    for (int i = 0; i < teamsCount; i++){
        teamFile << teams[i].name << " " << teams[i].coach << " " << teams[i].totalPoints << " " << teams[i].titles << endl;
    }
    teamFile.close();

    // Saving Users
    ofstream userFile("users.txt");
    for (int i = 0; i < usersCount; i++){
        userFile << users[i].username << " " << users[i].password << " " << users[i].role << endl;
    }
    userFile.close();

    // Saving Matches 
    ofstream matchFile("matches.txt");
    for (int i = 0; i < matchesCount; i++){
        matchFile << matches[i].team1 << " " << matches[i].team2 << " " << matches[i].date << " " << matches[i].status << " " << matches[i].time << " " << matches[i].score1 << " " << matches[i].score2 << endl; 
    }
    matchFile.close();

    // Saving Followers
    ofstream followFile("follow.txt");
    for (int i = 0; i < followCount; i++){
        followFile << follow[i].username << " " << follow[i].teamName << endl;
    }
    followFile.close();
}

void LoadData() {
    // Loading Teams 
    ifstream teamFile("teams.txt");
    if (teamFile.is_open()) { 
        while (teamFile >> teams[teamsCount].name >> teams[teamsCount].coach >> teams[teamsCount].totalPoints >> teams[teamsCount].titles) {
            teamsCount++;
        }
        teamFile.close();
    }

    // Loading Users
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        while (userFile >> users[usersCount].username >> users[usersCount].password >> users[usersCount].role) {
            usersCount++;
        }
        userFile.close();
    }

    // Loading Matches 
    ifstream matchFile("matches.txt");
    if (matchFile.is_open()) {
        while (matchFile >> matches[matchesCount].team1 >> matches[matchesCount].team2 >> matches[matchesCount].date >> matches[matchesCount].status >> matches[matchesCount].time >>matches[matchesCount].score1 >> matches[matchesCount].score2) {
            matchesCount++;
        }
        matchFile.close();
    }

    // Loading Followers
    ifstream followFile("follow.txt");
    if (followFile.is_open()) {
        while (followFile >> follow[followCount].username >> follow[followCount].teamName) {
            followCount++;
        }
        followFile.close();
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Hassan Badr

// Display_All_Matches
void Display_All_Matches()
{
    cout << "******************************************************\n";
    cout << "                     All Matches                      \n";
    cout << "******************************************************\n\n";

    for (int i = 0; i < matchesCount; i++)
    {
        if (matches[i].status == "upcoming" || matches[i].status == "past")
        {
            cout << "------------------------------------------------------\n";
            cout << "status:                        " << matches[i].status << endl;
            cout << "teams name:       " << matches[i].team1 << "                 " << matches[i].team2 << endl;
            cout << "score:                " << matches[i].score1 << "                      " << matches[i].score2 << endl;
            cout << "time:                         " << matches[i].time << endl;
            cout << "date:                        " << matches[i].date << endl;
            cout << "------------------------------------------------------\n\n";

        }
    }
}
// Display_past_matches
void Display_past_matches()
{
    cout << "******************************************************\n";
    cout << "                     Past Matches                     \n";
    cout << "******************************************************\n\n";

    for (int i = 0; i < matchesCount; i++)
    {
        if (matches[i].status == "past")
        {
            cout << "------------------------------------------------------\n";
            cout << "status:                        " << matches[i].status << endl;
            cout << "teams name:       " << matches[i].team1 << "                 " << matches[i].team2 << endl;
            cout << "score:                " << matches[i].score1 << "                      " << matches[i].score2 << endl;
            cout << "time:                         " << matches[i].time << endl;
            cout << "date:                        " << matches[i].date << endl;
            cout << "------------------------------------------------------\n\n";
        }
    }
}

// Display_upcoming_matches
void Display_upcoming_matches()
{
    cout << "******************************************************\n";
    cout << "                     upcoming Matches                 \n";
    cout << "******************************************************\n\n";

    for (int i = 0; i < matchesCount; i++)
    {
        if (matches[i].status == "upcoming")
        {
            cout << "------------------------------------------------------\n";
            cout << "status:                        " << matches[i].status << endl;
            cout << "teams name:       " << matches[i].team1 << "                 " << matches[i].team2 << endl;
            cout << "score:                " << matches[i].score1 << "                      " << matches[i].score2 << endl;
            cout << "time:                         " << matches[i].time << endl;
            cout << "date:                        " << matches[i].date << endl;
            cout << "------------------------------------------------------\n\n";
        }
    }
}


//check if user follow this team or not

int check_team_infollow(string teamname)
{
    for (int i = 0; i < followCount; i++)
    {
        if (teamname == follow[i].teamName && currentLoggedInUser == follow[i].username)
        {
            return i;
        }
    }
    return -1;
}


// function to unfollow

void unfollow_team()
{

    cout << "please enter the team which you want to unfollow\n";
    string team_name_for_unfollow;
    bool check2 = false;

    do {
        bool team_is_true = false;
        cin.ignore(1,'\n');
        getline(cin, team_name_for_unfollow);


        for (int q = 0; q < 20; q++)
        {
            if (team_name_for_unfollow == teams[q].name)
            {
                team_is_true = true;
                break;
            }
        }
        string options1;

        if (team_is_true == false)
        {
            cout << "******************\n";
            cout << " wrong name :( \n";
            cout << "******************\n";

            cout << "if you want to rewrite the team name press \"r\"   (if not enter any thing)\n";
            cin >> options1;
            if (options1 == "r" || options1 == "R")
            {
                cout << "please enter the team which you want to unfollow\n";
                continue;
            }
        else { break; }
        }

       


        int number_team_in_follow_list = check_team_infollow(team_name_for_unfollow);

        if (number_team_in_follow_list != -1 && team_is_true)
        {
            follow[number_team_in_follow_list].teamName = "";
            follow[number_team_in_follow_list].username = "";
            for (int j = number_team_in_follow_list; j < followCount - 1; j++)
            {
                follow[j].teamName = follow[j + 1].teamName;
                follow[j].username = follow[j + 1].username;
            }

            followCount--;
            cout << "You are no longer following " << team_name_for_unfollow << "." << endl;
            check2 = true;
        }

        else
        {
            cout << "this team does not exist in follow list\n";
            cout << "if you want to rewrite another team press \"r\"      (press \"x\" to exit )\n";
            string options2;
            cin >> options2;
            if (options2 == "r" || options2 == "R")
            {
                check2 = false;
            }
            else
            {
                check2 = true;
            }
        }
    } while (check2 == false);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Youssef�

void AddTeam()
{
    char choice;
    while (true)
    {


        //Making sure teams array limit has not been exceeded
        if (teamsCount >= 20)
        {
            cout << "Maximum number of teams already reached." << endl;
            return;
        }

        cin.ignore(1000, '\n');

        string newTeamName;
        bool isUnique;

        //Checking if team already exists
        do
        {
            cout << "Enter new team name: " << endl;
            getline(cin, newTeamName);
            isUnique = true;

            for (int i = 0; i < teamsCount; i++)
            {
                if (teams[i].name == newTeamName)
                {
                    cout << "Team already exists." << endl;
                    isUnique = false;
                }
            }
        } while (isUnique == false);

        teams[teamsCount].name = newTeamName;
        teams[teamsCount].totalPoints = 0;
        teams[teamsCount].titles = 0;
        cout << "Enter the new team's coach's name: " << endl;
        getline(cin, teams[teamsCount].coach);
        teamsCount++;

        cout << "Team " << newTeamName << " added" << endl;

        cout << "Do you want to add another team? (y/n)" << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n')
            return;
    }
}

void AddUpcomingMatch()
{
    char choice;

    while (true)
    {
        //Making sure matches array limit has not been exceeded
        if (matchesCount >= 200)
        {
            cout << "Maximum number of matches already reached." << endl;
            return;
        }

        cin.ignore(1000, '\n');

        string teamOne, teamTwo;
        bool doesExist;

        //Making sure both teams actually exist
        do
        {
            char addchoice;

            if (teamsCount < 2)
            {
                cout << "You can't schedule a match with less than two teams! Would you like to add teams? (y/n)" << endl;
                cin >> addchoice;
                if (addchoice == 'Y' || addchoice == 'y')
                    AddTeam();
                else
                    return;
            }

            cout << "Would you like to add teams before scheduling a match? (y/n)" << endl;
            cin >> addchoice;
            if (addchoice == 'Y' || addchoice == 'y')
                AddTeam();

            cin.ignore(1000, '\n');

            doesExist = true;
            bool team1Exists = false;
            bool team2Exists = false;

            cout << "Enter team 1 name:" << endl;
            getline(cin, teamOne);
            cout << "Enter team 2 name:" << endl;
            getline(cin, teamTwo);

            for (int i = 0; i < teamsCount; i++)
            {
                if (teams[i].name == teamOne)
                    team1Exists = true;
            }
            for (int i = 0; i < teamsCount; i++)
            {
                if (teams[i].name == teamTwo)
                    team2Exists = true;
            }
            if (team1Exists == false)
            {
                cout << "Team 1 does not exist!" << endl;
                doesExist = false;
            }
            if (team2Exists == false)
            {
                cout << "Team 2 does not exist!" << endl;
                doesExist = false;
            }

        } while (doesExist == false);

        matches[matchesCount].team1 = teamOne;
        matches[matchesCount].team2 = teamTwo;
        cout << "Enter match date (DD/MM/YYYY): " << endl;
        cin >> matches[matchesCount].date;
        matches[matchesCount].status = "upcoming";
        matches[matchesCount].score1 = 0;
        matches[matchesCount].score2 = 0;
        matchesCount++;

        cout << "Do you want to add another match? (y/n)" << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n')
            return;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////Hassan Tarek

//////////////////////////////////////// update match result (function definition)
void UpdateMatchResult(){
    
/////////////////////////////////////// print the upcoming matches
    cout<<"update match results"<<endl;
    bool upcoming = false ;
    cout<<"current upcoming matches"<<endl;
      for ( int i = 0 ; i < matchesCount ; i++ ){

        if( matches[i].status == "upcoming" ){
            cout<<matches[i].team1<<" "<<matches[i].team2<<" "<<matches[i].date<<" "<<matches[i].time<<endl;         
              upcoming = true ;
        }
    }

  if(!upcoming){

    cout<<"there is no upcoming matches :("<<endl;
    return;

  }



///////////////////// input the two teams
string input_team1 ;
string input_team2 ;

cout<<"enter team 1"<<endl;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
getline(cin, input_team1);

cout<<"enter team 2"<<endl;
getline(cin, input_team2);


//////////////////// search for the match 
bool matchfound = false ;

    for ( int i = 0 ; i < matchesCount ; i++ ){  

        if (((matches[i].team1 == input_team1 && matches[i].team2 == input_team2) || 

        (matches[i].team1 == input_team2 && matches[i].team2 == input_team1)) && 

        matches[i].status == "upcoming"){

          cout<<"Match found!"<<endl;
          cout<<"Enter final score for "<< matches[i].team1<<endl;
          cin>>matches[i].score1;    

          cout<<"Enter final score for "<< matches[i].team2<<endl;
          cin>>matches[i].score2;

          matches[i].status = "past";  
          
            if (matches[i].score1 > matches[i].score2){  /////////// Team 1 wins


              for (int j = 0; j < teamsCount; j++) {

                if (teams[j].name == matches[i].team1) 
                teams[j].totalPoints += 3;

                }
            } 
            else if (matches[i].score2 > matches[i].score1){ /////////// Team 2 wins
    
                for (int j = 0; j < teamsCount; j++){

                  if (teams[j].name == matches[i].team2) 
                  teams[j].totalPoints += 3;
    
                }   
            }

            else { /////////// draw

               for (int j = 0; j < teamsCount; j++){

                 if (teams[j].name == matches[i].team1)
                   teams[j].totalPoints += 1;

                 if (teams[j].name == matches[i].team2)
                   teams[j].totalPoints += 1;

               }
            }


          cout<<"Match updated successfully!"<<endl;
          matchfound = true;
          break;

        }

    }

    if(!matchfound)
    cout <<"Error: Match not found or it is already played.Please check your spelling :)"<< endl;


}




///////////////////////////////////league leaderboard function defenition (extra function)
void leagueleaderboard(){




for (int i = 0 ; i < teamsCount-1  ; i++){

    for (int j = 0 ; j < teamsCount-i-1 ; j++){

       if( teams[j].totalPoints < teams[j+1].totalPoints)

         swap(teams[j] , teams[j+1]) ;
         
    }
    
}


    
cout << "========================================================"<<endl;
    cout << "                  🏆 LEAGUE LEADERBOARD 🏆                  "<<endl;
    cout << "========================================================"<<endl;
   
    cout << left << setw(10) << "Rank" 
         << setw(20) << "Team Name" 
         << setw(15) << "Points" 
         << setw(10) << "Titles" << endl;
    cout << "--------------------------------------------------------"<<endl;

    
    for (int i = 0; i < teamsCount; i++) {
        cout << left << setw(10) << (i + 1)            
             << setw(20) << teams[i].name 
             << setw(15) << teams[i].totalPoints 
             << setw(10) << teams[i].titles << endl;
    }
    cout << "========================================================"<<endl;






}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Joe 

string inputPassword() {
    string password = "";
    int ch;

    while (true) {
        ch = _getch();

        if (ch == 13) { // ASCII code for Enter
            break;
        }
        else if (ch == 8) { // ASCII code for Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // **|* -> ** | -> **|
            }
        }
        else {
            password += (char)ch;
            cout << "*";
        }
    }

    cout << '\n';
    return password;
}

void Register() {
    User newUser;

    // SIZECHECK
    if (usersCount >= 100) {
        cout << "User limit reached!\n";
        return;
    }

    // SAFETYCHECK
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores everything till it finds \n 

    // USERNAME
    while (true) {

        cout << "Enter username (or 0 to cancel): ";
        getline(cin, newUser.username);

        if (newUser.username == "0") {
            cout << "Registration canceled!\n";
            return;
        }

        bool validUsername = true;
        for (int i = 0; i < usersCount; i++) {
            if (users[i].username == newUser.username) {
                cout << "Username already exists!\n";
                validUsername = false;
                break;
            }
        }

        if (validUsername)break;
    }


    // PASSWORD
    while (true) {

        cout << "Enter password (or 0 to cancel): ";
        newUser.password = inputPassword();

        if (newUser.password == "0") {
            cout << "Registration canceled!\n";
            return;
        }

        if (newUser.password.length() < 4) {
            cout << "Password too short!\n";
        }
        else {
            break;
        }
    }


    // ROLE
    while (true) {

        cout << "Enter role (admin/user) (or 0 to cancel): ";
        cin >> newUser.role;

        if (newUser.role == "0") {
            cout << "Registration canceled!\n";
            return;
        }

        // convert to lowercase
        for (char& c : newUser.role) {
            c = tolower(c);
        }

        if (newUser.role == "admin" || newUser.role == "user") {
            break;
        }
        cout << "Invalid role! Please enter admin or user.\n";
    }

    //SAVEUSER
    users[usersCount] = newUser;
    usersCount++;

    cout << "Registered successfully!\n";
}

void Login() {

    // SAFETYCHECK
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {

        string username, password;

        cout << "Enter username (or 0 to cancel): ";
        getline(cin, username);

        if (username == "0") {
            cout << "Login canceled!\n";
            return;
        }

        cout << "Enter password (or 0 to cancel): ";
        password = inputPassword();

        if (password == "0") {
            cout << "Login canceled!\n";
            return;
        }

        for (int i = 0; i < usersCount; i++) {
            if (users[i].username == username && users[i].password == password) {

                currentLoggedInUser = username;
                currentUserRole = users[i].role;

                cout << "Login successful!\n";
                cout << "Role: " << currentUserRole << endl;
                return;
            }
        }

        cout << "Invalid username or password!\n";

        while (true) {
            char choice;
            cout << "Try again? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
                cout << "Invalid choice!\n";
                continue;
            }

            if (choice == 'n' || choice == 'N') {
                return;
            }

            break;
        }
    }
}

void Logout() {
    currentLoggedInUser = "";
    currentUserRole = "";

    cout << "Logged out successfully!\n";
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Moaz
void displayfollowedmatch() {
    string followtemp[10];
    int j=0;
    bool flag = false;
    cout << "\t  Matches for followed teams\n";
    for (int i = 0; i < followCount; i++) {//loop to store fav teams
        if (currentLoggedInUser==follow[i].username) {
            followtemp[j]=follow[i].teamName;
            j++;
            flag = true;
        }
    }
    if (flag){
        for (int i = 0; i < matchesCount; i++) {
            for (int z=0; z<10; z++) {//loop through matches and display followed  matches only
                if (matches[i].team1==followtemp[z]||matches[i].team2==followtemp[z]) {
                    cout<<"\t"<<matches[i].team1<<" "<<matches[i].score1<<"\t"<<"v.s\t"<<matches[i].score2<<matches[i].team2<<endl;
                    cout<<"\t\t"<<"Date is : "<<matches[i].date<<endl;
                    cout<<"\t\t"<<"time is : "<<matches[i].time<<endl;
                
                    break;
                }
            }
        }
        cout<<"**********************    Feed for fav Teams  ****************\n";
        for (int i = 0; i < 10; i++) {
            for (int z=0; z<20; z++) {//loop through all teams to get followed 
                 if (followtemp[i]==teams[z].name) {//display data
                    if(followtemp[i]=="")continue;
                    else{
                     cout<<"team name is  "<<teams[z].name<<endl;
                     cout<<"coach name is "<<teams[z].coach<<endl;
                     cout<<"Total points : "<<teams[z].totalPoints<<endl;
                     if (teams[z].titles==0) cout<<"You have no titles better luck with coach "<<teams[z].coach<<endl;
                     else cout<<"Total titles : "<<teams[z].titles<<endl;
                     break;}
                 }
            }
        }
    }
    else cout<<"please follow a team";
}

void gameoftheweek() {//extra function
    if (matchesCount == 0) {
        cout << "\n[Notice] No matches scheduled yet for the Game of the Week.\n";
        return;
    }
    int matchhnum=rand()%matchesCount;//generate match random as match of the week
    cout << "\n******************************************" << endl;
    cout << "        🏆 GAME OF THE WEEK 🏆            " << endl;
    cout << "******************************************" << endl;
    cout<<matches[matchhnum].team1<<" "<<matches[matchhnum].score1<<"\t"<<"v.s\t"<<matches[matchhnum].team2<<" "<<matches[matchhnum].score2<<endl;
    cout<<"\t"<<"status is : "<<matches[matchhnum].status<<endl;
    cout<<"\t"<<"Date is : "<<matches[matchhnum].date<<endl;
    
    cout << "******************************************" << endl;
}
//--------------------------------------------------------------
//Muhammad
void FollowTeam() {
    cout<<"Please enter the name of the team you want to follow (Or Enter 0 to return to main menu again): "<<endl;
    string TeamName;
    bool TeamExists=false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do{
        getline(cin,TeamName);
        if (TeamName =="0") {
            break;
        }
        for (int i = 0; i <20; i++) {
            if (TeamName==teams[i].name) {
                TeamExists=true;
                if (followCount<200) {
                    follow[followCount].username=currentLoggedInUser;
                    follow[followCount].teamName=TeamName;
                    followCount++;
                    cout<<"You are now following "<<" "<<TeamName<<endl;
                }
            }
        }
        if (TeamExists==false) {
            cout<<"Team doesn't exist ,Please make sure you entered the correct name and try again (Or Enter 0 to return to main menu again) "<<endl;
        }


    }while (TeamExists==false);
}

void FilterMatchesByTeam() {
    cout<<"Which team do you want to view their matches ? (Or Enter 0 to return to main menu again):"<<" ";
    string ChosenTeam;
    bool TeamExists = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do{
        getline(cin,ChosenTeam);
        if (ChosenTeam=="0") {
            break;
        }
            for (int i = 0; i <20; i++) {
            if (ChosenTeam==teams[i].name) {
                TeamExists = true;
                cout<<"Here are the matches of "<<" "<<ChosenTeam<<" "<< ":"<<endl;
                for (int j = 0;j<200;j++) {
                    if (ChosenTeam==matches[j].team1 || ChosenTeam==matches[j].team2) {
                        cout<<"Date : "<<matches[j].date<<endl;
                        cout<<matches[j].team1 <<" "<<"Vs"<<" "<<matches[j].team2;
                        cout<<"Status : "<<matches[j].status<<endl;
                        if (matches[j].status=="Finished" || matches[j].status=="finished") {
                            cout<<matches[j].score1<<" --"<<matches[j].score2<<endl;
                        } else cout<<"Match is yet to be played"<<endl;
                    }
                }break;
            }

        }  if (TeamExists==false) cout<<"Invalid team name , please check the team name and try again (Or Enter 0 to return to main menu again):"<< " ";



    }while (TeamExists == false);
}

int MainMenuOption() {
    cout<<"Press 1 to Sign up."<<endl;
    cout<<"Already have an account ? Press 2 to sign in. "<<endl;
    int result;
    while (true) {
        cin>>result;
        if (result == 1||result==2) {
            return result;
        }   cout<<"Incorrect option , please Try again "<<endl;
        cout<<"Are you a user ? Press 1 to sign in to your account"<<endl;
        cout<<"Are you an admin ? Press 2 to sign in to your account"<<endl;
    }
}

bool AskToContinue() {
    char answer;
    cout<<"Would you like to continue using the app ? Press Y if yes , N if no "<<"   ";
    while (true) {
        cin>>answer;
        if (answer == 'N' || answer == 'n') {
            cout<<"Thank you for using our football app !"<<endl<<" Make sure to check again for the lastest news regarding your favorite team."<<endl;
            return false;
        }
        if (answer=='Y' || answer=='y') {
            return true;
        }
        cout<<"Option is incorrect , Please try again "<<endl;
    }
}

void AdminMenu() {
    int ChoiceAdmin;
    while(true) {
        cout << "--- What would you like to do? ---"<<endl
        <<"1. Add a team"<<endl
        <<"2. Add an upcoming match"<<endl
        <<"3. Update match results "<<endl
        <<"4. to logout"<<endl;
        cin>>ChoiceAdmin;
        if (ChoiceAdmin==1){
            AddTeam();
        }

        if (ChoiceAdmin==2){
            AddUpcomingMatch();
        }
        if (ChoiceAdmin==3) {
            UpdateMatchResult();
        }

        if (ChoiceAdmin==4){
            Logout();
            break;
        }
    }
}

void UserMenu() {
    int ChoiceUser;


    
    while(true) {
        cout << "--- What would you like to do? ---"<<endl
    << "1. Follow a team"<<endl
    << "2. Unfollow a team"<<endl
    << "3. View a specific team's matches"<<endl
    << "4. Display your followed matches feed"<<endl
    << "5. View all games"<<endl
    << "6. View past games"<<endl
    << "7. View upcoming games"<<endl
    << "8. View league leaderboard"<<endl
    << "9. Logout"<<endl;
        cin>>ChoiceUser;

        if (ChoiceUser==1){
            FollowTeam();
         }

        if (ChoiceUser==2){
            unfollow_team();
            }
        if (ChoiceUser==3) {
            FilterMatchesByTeam();
        }
        if (ChoiceUser==4) {
            displayfollowedmatch();
        }
        if (ChoiceUser==5) {
            Display_All_Matches();
        }
        if (ChoiceUser==6) {
            Display_past_matches();

        }
        if (ChoiceUser==7){
            Display_upcoming_matches();
            }

        if (ChoiceUser==8) {
            leagueleaderboard();
        }
            
        if (ChoiceUser==9){
            Logout();
            break;
            }

    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
   srand(static_cast<unsigned int>(time(0)));
    LoadData();
    cout<<"Welcome to CounterAttack , The number 1 app for all Football team  news regarding your favorite teams and world-wide football"<<endl;
    gameoftheweek();
    while (true) {
        int option=MainMenuOption();
        if (option==1) {
            Register();                    //handle registering



        }

        else if (option==2) {
            Login();            //handles Sign in
            if (currentUserRole == "admin") {
                AdminMenu();

            }
            else if (currentUserRole == "user") {
                UserMenu();
            }


            if (AskToContinue()==false) {
                break;
            }

        }
    }
    SaveData();
    system("pause");
    return 0 ;
}
