#include<iostream>//iostream
#include<string>//string
#include<thread>//thread
#include<chrono>//chrono
#include<algorithm>//transfer
#include<fstream>//file
#include<cctype>//tolower
#include<vector>
#include<random>

using namespace std;

//point for each question
const int Q_score=5;

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
    cout<<"\033[1;31m                         ThinkFast Quiz Application \033[22m" ;
    cout<<"\033[1;31m"<<endl;
    asteriks(70);
}

//system clear function
void clear_screen(int i){

    this_thread::sleep_for(chrono::seconds(i));
    system("cls");
}

void instruction(){
    
    cout<<"\033[1;32m Read the Instruction Carefully! "<<endl;
    cout<<"(1). READ THE QUESTION CAREFULLY"<<endl;
    cout<<"(2). EACH QUESTION CARRY 5 MARKS"<<endl;
    cout<<"(3). TOTAL TEST CONSIST 50 MARKS."<<endl;
    cout<<"(4). No Negative marking"<<endl;
    cout<<"(5). good luck\033[0m"<<endl;
}

//valid username input
// Function to validate username input by ensuring it contains only letters and spaces.

bool valid_user_input(string& username){
    while(true){
        cout<<"Enter your name : "<<endl;
        getline(cin,username);
        bool valid=true;
        // Check for non-alphabetical characters or special characters in the username.
        for(char ch:username){
            if(!isalpha(ch)&& ch != ' '){
                valid =  false;
                break;
            }
        }

        if(username.empty()){
            cout<<"\033[31mInvalid input. username cannot be empty.\033[0m"<<endl;
            continue;
        }

        else if(!valid){
            
            cout<<"\033[32mInvalid input!. Username should only contain letters or spaces.\033[0m"<<endl;
            clear_screen(2);
            interface();
        }
        //for sucessfull implementation return true means usernaem is valid
        else{
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
        cout<<"\033[31mPlease enter the valid class (e.g., SE02, SE01,CS01,CS02)\033[0m"<<endl;
        clear_screen(2);
        interface();
        }
    }
}

//quiz function
void quiz( ofstream &write ){
    vector<pair<string,char>> questions{
        {"\033[1;33m Who is the founder of C++ : \033[0m\n\033[34m(a)jeff bezzos \n(b)alan turing \n(c)Bjarne strousstrup \n(d)N.O.T \033[0m",'C'},
        {"\033[1;36m What is the early name of C++ : \n(a) cpp. \n(b) C with classes \n(c) C \n(d) All of These.\033[0m",'B'},
        {"\033[1;32m Which of the following is used to declare a \n in C++ : \n(a) var x;\n(b) int x; \n(c)declare int x; \n(d) All of These\033[0m",'B'},
        {"\033[1;35m which one is Data type : \n(a) int\n(b) if-else \n(c)for \n(d) All of These\033[0m",'A'},
        {"\033[1;36m What is the correct syntax to print Hello, World! in C++? : \n(a) echo Hello, World!\n(b) cout << Hello, World!; \n(c)print(Hello, World!) \n(d) N.O.T\033[0m",'B'},
        {"\033[1;37m Which of the following data types can store a floating-point number in C++? : \n(a) int\n(b) char \n(c)float \n(d) All of These\033[0m",'C'},
        {"\033[1;36m What is the capital of Palestine? : \n(a) Jerusalem\n(b) Ramallah \n(c)Gaza \n(d) Bethlehem\033[0m",'B'},
        {"\033[1;35m Which of the following is a correct way to declare a pointer in C++? : \n(a) int* ptr;\n(b) ptr int*; \n(c)pointer int*; \n(d) int ptr*;\033[0m",'A'},
        {"\033[1;34m What is the purpose of the delete operator in C++? : \n(a) It initializes variables\n(b) It is used for deallocating stack memory \n(c)t frees the dynamically allocated memory. \n(d) It returns memory to the heap\033[0m",'C'},
        {"\033[1;34m What is the name of the first artificial Earth satellite? : \n(a) Voyager 1\n(b) Hubble \n(c)Apollo 11. \n(d) Sputnik 1\033[0m",'C'},
        
    };
    random_device rd;
    mt19937 g(rd());
    //shuffling question start from the value of g
    shuffle(questions.begin(),questions.end(),g);
    int score =0;
    char answer;
     
    for(auto&  q: questions){
        do{
        //equalizing the pair of vector of string and char to q
        cout<<q.first<<"\n\033[36mYour Answer : ";
        // q.first the string of pair because the string is in first to order
        cin>>ws;//to ignore spaces or enter accidently press by the user 
        answer=cin.get();
        //ignore extra input 
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"\033[0m";
        answer=toupper(answer);
        if(answer!='A' &&answer!='B'&&answer!='C'&&answer!='D'){
            cout<<"Invalid choice! Please enter A,B,C or D."<<endl;
        }
        }while(answer!='A' &&answer!='B'&&answer!='C'&&answer!='D');
        if(answer == q.second){
            score+=Q_score;
            cout<<"\033[32mCorrect!\033[0m"<<endl;
            //adding 5 marks on the righht answer
        } else {
            cout<<"\033[31mIncorrect The correct answer is \033[0m"<<q.second<<"."<<endl;
        }
        clear_screen(1);
    }
    cout<<"\033[35mYour final score is : "<<score<<"/"<<questions.size()*5<<"\033[0m"<<endl;
   // Write the user's data (name, class, and score) to the file after the quiz.

    if (write.is_open()){
        write << "Final Score : "<<score<<"/"<<questions.size()*5<<endl;
    }
    else{
        cout<<"\033[31mError unable to open the file \033[0m"<<endl;
    }
}


//main function
int main(){
    string username,Class;
    
    interface();

    ofstream write("USERdata.txt",ios::app);
    if(valid_user_input(username)){
        valid_classinput(Class);
        if(write.is_open()){
            write<<"User name : "<<username<<endl;
            write<<"class : "<<Class<<endl;
            
        }else{
            cout<<"Error: Unable to open file for writing."<<endl;
        }
        clear_screen(2);
        interface();
        cout<<"hi "<<username<<endl;
        instruction();
        system("pause");
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
        char choice;
        do{
        quiz(write);
        cout<<"\033[1;34mDo you want to play again? (Y/N): \033[0m";
        cin>>choice;
        }while(choice=='y'||choice=='Y');
        write.close();

    }

    return 0;       
}
