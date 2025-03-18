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
    cout<<"(4). No Negative marking"<<endl;
    cout<<"(5). good luck"<<endl;
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
        }
        //for special character or non alphabet
        else if(!valid){
            /*if after checking complete through for each loop if there any non character
            or special the condition make valid bool false so using this condition reset the screen 
            and give more chances to user again input*/
            cout<<"033[32mInvalid input!. Username should only contain letters or spaces.033[0m"<<endl;
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
void quiz(  ){
    vector<pair<string,char>> questions{
        {"Who is the founder of C++ : \n(a)jeff bezzos \n(b)alan turing \n(c)Bjarne strousstrup \n(d)N.O.T ",'C'},
        {"What is the early name of C++ : \n(a) cpp. \n(b) C with classes \n(c) C \n(d) All of These.",'B'},
        {"which one is Data type : \n(a) int\n(b) if-else \n(c)for \n(d) All of These",'A'},
        
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
        cout<<q.first<<"\nYour Answer : ";
        // q.first the string of pair because the string is in first to order
        cin>>answer;
        answer=toupper(answer);
        if(answer!='A' &&answer!='B'&&answer!='C'&&answer!='D'){
            cout<<"Invalid choice! Please enter A,B,C or D."<<endl;

        }
        }while(answer!='A' &&answer!='B'&&answer!='C'&&answer!='D');
        if(answer == q.second){
            score+=5;
            cout<<"\033[32mCorrect!\033[0m"<<endl;
            //adding 5 marks on the righht answer
        } else {
            cout<<"\033[31mIncorrect The correct answer is \033[0m"<<q.second<<"."<<endl;
        }
        clear_screen(1);
    }
    cout<<"Your final score is : "<<score<<"/"<<questions.size()*5<<endl;
    ofstream write("USERdata.txt",ios::app);
    if (write.is_open()){
        write << "Final Score : "<<score<<"/"<<questions.size()*5<<endl;
        write.close();
    }
    else{
        cout<<"Error unable to open the file "<<endl;
    }
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
        quiz();

    }

    return 0;       
}
