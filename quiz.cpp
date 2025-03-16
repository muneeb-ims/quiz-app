#include<iostream>//iostream
#include<string>//string
#include<thread>//thread
#include<chrono>//chrono
#include<algorithm>//transfer
#include<fstream>//file
#include<cctype>//tolower
#include<vector>

using namespace std;



//stars print
void asteriks(int n){
    int i=1;
    while(i<=n){
    cout<<"*";
    this_thread::sleep_for(chrono::milliseconds(3));
    i++;
    }

    cout<<endl;
}

// heading
void interface(){
    asteriks(70);
    cout<<"\033[1;31m                         Smart Quiz Application \033[22m" ;
    cout<<"\033[31m"<<endl;
    asteriks(70);
}

//system clear function
void clear_screen(int i){

    this_thread::sleep_for(chrono::seconds(i));
    system("cls");
}

void instruction(){
    
    cout<<"\033[32m Read the Instruction Carefully! "<<endl;
    cout<<"(1). READ THE QUESTION CAREFULLY"<<endl;
    cout<<"(2). EACH QUESTION CARRY 5 MARKS"<<endl;
    cout<<"(3). TOTAL TEST CONSIST 50 MARKS."<<endl;
    cout<<"(4). good luck"<<endl;
    cout<<"Get Ready! Your Quiz Will Begin In 10 Seconds!"<<endl;
    clear_screen(10);

}

//valid username input
/*check username input by making parameter refrence variable so the change in variable cause effect to 
refrence variable
then using getline to take input for multiple word 
*/
bool valid_user_input(string& username){
    while(true){
        cout<<"Enter your name : "<<endl;
        getline(cin,username);
        bool valid=true;
        for(char ch:username){
            if(!isalpha(ch)&& ch != ' '){
                valid =  false;
                break;
            }
        }

        if(username.empty()){
            cout<<"Invalid input. username cannot be empty."<<endl;
            clear_screen(2);
            interface();
        }else{
            return true;
        }
    }
}


//valid Class input function.
bool valid_classinput(string& Class){
    while(true){
        cout<<"Enter your Class (e.g, se02,se01,cs01): "<<endl;
        getline(cin,Class);
        transform(Class.begin(),Class.end(),Class.begin(),::tolower);
        if(Class == "se01" || Class == "se02" || Class == "cs01" || Class == "cs02" || Class == "cs03"){
        return true;
    }else{
        cout<<"Please enter the valid class (e.g., SE02, SE01,CS01,CS02)"<<endl;
        clear_screen(2);
        interface();
        }
    }
}

//quiz function
void quiz(){
    vector<pair<string,char>> questions{
        {"Who is the founder of C++ : \n(a)jeff bezzos \n(b)alan turing \n(c)Bjarne strousstrup \n(d)N.O.T ",'C'},
        {"What is the early name of C++ : \n(a) cpp. \n(b) C with classes \n(c) C \n(d) All of These.",'B'},
        {"which one is Data type : \n(a) int\n(b) if-else \n(c)for \n(d) All of These",'A'},
        
    };
    int score =0;
    char answer;
     
    for(auto&  q: questions){
        cout<<q.first<<"\nYour Answer : ";
        cin>>answer;
        answer=toupper(answer);
        if(answer == q.second){
            score+=5;
        } else {
            score-=5;
        }
    }
    if (score < 0) score = 0;
    cout << "Total Score: " << score << endl;
}


//main function
int main(){
    string username,Class;
    
    interface();

    if(valid_user_input(username)){
        valid_classinput(Class);
        ofstream write("USERdata.txt");
        if(write.is_open()){
            write<<"User name : "<<username<<endl;
            write<<"class : "<<Class<<endl;
            write.close();
        }
        clear_screen(2);
        interface();
        cout<<"hi "<<username<<endl;
        instruction();

        
        quiz();

        cout << "Thanks for visiting!";
    }

    return 1;
}
