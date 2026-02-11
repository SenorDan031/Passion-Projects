    /*
    What's new:
    
    VERSION 0.0.1 : :  January 31st, 2026
        ***************************************************************************************************
        --> Seperated data processing and UI processing from main ()

        --> Created  function where data and UI is processed [Fn name: display Stats() ; Fn type: VOID]

        --> Ensured that array gets cleared before new data entry

        --> Improved UI/UX with better prompts and messages

        --> Reduced time delays for snappier experience

        --> Changed vector arry datatypefrom float -> int for efficiency

        --> Removed unncessary loops and logics

        --> Added a logic in class regdata where, adding a tag extends the dataa array automatically {Scope of Affect: entire program}

    ***************************************************************************************************


    VERSION 0.0.2 : :  February 2nd, 2026
        ***************************************************************************************************
        --> Added a child class ACS_CALCI, this class now handles ACS calculation, Rank and Tier distribution

        --> Moved relevant functions to ACS_CALCI class from main class regdata

        --> Improved Tier distribution logic with better messages and more accurate tier distribution

        --> Improved overall code structure for better readability and maintainability

        --> Added a function 'PASS_KEY()' [Fn Type: VOID], locks Combat card behind a security pass key, if correct pass key is input, combat card is revealed then only

    ***************************************************************************************************

    VERSION 0.0.3 : :  February 4th, 2026
        ***************************************************************************************************
        --> Added a child class Agents, this class now Guides the player as for which agent class to pick and how to utilize their abilities for maximum impact and gains

        --> Added a function 'Agent_Guide()' [Fn Type: VOID], this function suggests the player for which agent class to pick based on their overall ACS and match stats

        --> Added a function 'Display_KD_Graph()' [Fn Type: VOID], this function Represents player's Kills, Deaths and K/D ratio in a graphical way with impact markers to show player's performance in a more visual way
        
    ***************************************************************************************************


    */


    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <windows.h>
    #include <cmath>
    #include <vector>
  #include "../Utils_files_/colors.h"

    using namespace std;

    class regdata{    //This class here gathers overall match stats from the user
        
        protected:
        
        vector <int> match_data;
            const vector<string> TAGS={"Kills","Deaths","Assists","Rounds Won","Rounds Lost","FB"};  //current tags size: 6 [More will be added in future patches]

        public:

        

        void collect_data(){
        match_data.clear();  
        int val;
        cout<<YELLOW<<"\t\t>>>> Enter the required data <<<<"<<endl;
        for(const string& tag : TAGS){
            cout<<MAGENTA<<" >>>No. of  "<<tag<<" : "; cin>>val; match_data.push_back(val);
        }}

        const vector<string>& get_TAGS() const { return TAGS; }
        
        const  vector<int>& data_array() const {
                return match_data;
            }
    };

    class ACS_CALCI : public regdata{      //This class here will calculate the ACS of the player 
                                        //Based on ACS, Player's Rank and Tier will be decided and required suggestions be given
            private:   

            string pass_key="valo26ACS";       
        
            float ACS(){
                float acs=0; int fb=170;
                for(int i=match_data[5];i>0;i--){

                    if(i>0){
                        if(fb>=0){
                            acs+= (float) fb;  //F.B. bonus starts from 170 and decreases by 20 for each First Kills
                        }
                    }
                    fb-=20;
                    if(fb<0) fb=0; //Ensures that F.B. bonus >  0
            }
            acs+= (float) (match_data[0]-match_data[5])*125;  //For each kills fter first bloods +120/Kill(s)
            acs+= (float) match_data[2]*30; //For each assists get +30
            acs+= (float) (match_data[3]*10.5)- (float)(match_data[4]*5);  
            //For each round won get +10.5 and for each loss get -5

            //Total Acs is divided by total round played to get average combat score
            if(match_data[3]+match_data[4]>0) acs/= (float) (match_data[3]+match_data[4]);
            
            else acs=0;

            return acs;}

            public :

            float scores=ACS();

            string Rank(float scores){ 
                //This Function decides player's rank based on thier overall ACS

                if(scores<600 && scores>=450){
                    return "Radiant";
                }else if(scores<450 && scores>=300){
                    return "Immortal - Ascendant";
                }else if(scores<300 && scores>=250){
                    return "Diamond - Platinum";
                }else if(scores<250 && scores>=195){
                    return "Gold - Silver";
                }else  return "Bronze and Below";}

                string Tier(float scores){ 
                    //This Function decides player's tier based on the Doubling of thier overall ACS value
                    
                    if(scores*2>=1000 && scores*2<=2000){
                        cout<<YELLOW<<"\n\t>>> You are in Top 1% Players tier, globally! Keep clipping those taps! <<<"<<RESET<<endl;
                        
                        return "Tier:> SSS";
                    }else if(scores*2>=800 && scores*2<1000){

                        cout<<YELLOW<<"\n\t>>> You are in TOP 5% PLayers tier, globally! Keep climbing up the ladder, Your are ALMOST THERE! <<<"<<RESET<<endl;

                        return "Tier:> SS";
                    }else if(scores*2>=650 && scores*2<800){
                        cout<<GREEN<<"\n\t>>> You are in TOP 10% Players tier, globally! Good going, Keep on FIGHTING YOUR WAY UP!! <<<"<<RESET<<endl;

                        return "Tier:> S";
                    }else if(scores*2>=500 && scores*2<650){
                        cout<<GREEN<<"\n\t>>> You are in TOP 25% Players tier, globally! Not bad, but you can do BETTER! <<<"<<RESET<<endl;

                        return "Tier:> A";
                    }else if(scores*2>=400 && scores*2<500){
                        cout<<BLUE<<"\n\t>>> You are in TOP 50% Players tier, globally! You need to step up your game! <<<"<<RESET<<endl;

                        return "Tier:> B";
                    }else if(scores*2>=300 && scores*2<400){
                        cout<<BLUE<<"\n\t>>> You are in TOP 75% Players tier, globally! You need to practice more! <<<"<<RESET<<endl;

                        return "Tier:> C";
                    }else if(scores*2>=200 && scores*2<300){
                        cout<<RED<<"\n\t>>> You are in BOTTOM 25% Players tier, globally! Work hard to improve your skills! <<<"<<RESET<<endl;

                        return "Tier:> D";
                    }else{
                        cout<<RED<<"\n\t>>> You are in BOTTOM 10% Players tier, globally! Don't be disheartened, EVERYONE starts somewhere! KEEP TRYING! <<<"<<RESET<<endl;

                        return "Tier:> E";
                    }

                }

                void display_SRT(){ //This Function displays all 3 SRT values

                    cout<<BG_BLUE<<"\n\t\t>>> Player's Combat Card <<<"<<RESET<<endl;

                    cout<<MAGENTA<<"\n\t Average Combat Score (ACS) : "<<YELLOW<<scores<<RESET<<endl; 
                    //Above shows player's ACS

                    cout<<MAGENTA<<"\n\t Player's Placement Rank : "<<YELLOW<< Rank(scores)<<RESET<<endl;
                    //Above shows player's Rank

                    cout<<MAGENTA<<"\n\t Player's Placement Tier : "<< Tier(scores)<<RESET<<endl;
                    //Above shows player's Tier

                }  //SRT stands for overall Score, Rank and Tier

                public :

                void PASS_KEY(){   //Locks ACS behind a security pass key, makes combat card accessible only when the right passkey is entered

                    string input_pass_key; cin>>input_pass_key;

                    system("cls");

                    if(input_pass_key==pass_key)   display_SRT();

                    else cout<<RED<<"Wrong input!!Enter valid details to view player combat card!!!"<<RESET<<endl;

                }

    };

    class Agents : public ACS_CALCI{

        //This Class will process the data retrieved from class ACS_CALCI and based on that give guide to the user for which agent to pick or what gamestyle to adapt

        public :

        void Display_KD_Graph() {
                float kills = (float)match_data[0];
                float deaths = (float)match_data[1];
                float ratio = (deaths > 0) ? (kills / deaths) : kills;

                cout << CYAN << "\n\t[ Performance Visualizer ]" << RESET << endl;
                cout << "\tKills:  ";
                for(int i=0; i < kills/2; i++) cout << GREEN << "█"; 
                cout << " " << kills << endl;

                cout << "\tDeaths: ";
                for(int i=0; i < deaths/2; i++) cout << RED << "█"; 
                cout << " " << deaths << endl;

                cout << "\n\tK/D Ratio: " << YELLOW << ratio << RESET << endl;
                
                // Impact Marker
                if(ratio >= 1.5) cout << "\tStatus: " << BG_GREEN << " DOMINATING " << RESET << endl;
                else if(ratio >= 1.0) cout << "\tStatus: " << BG_BLUE << " IMPACTFUL " << RESET << endl;
                else cout << "\tStatus: " << BG_RED << " STRUGGLING " << RESET << endl;

        }

        void Agent_Guide(){
            
            cout<<CYAN<<"\n\t\t>>> TIPS FOR CHOOSING AGENTS BASED ON YOUR ACS VALUE <<<"; cout<<RESET<<endl;
            cout<<GREEN<<"\n\t Upon interpreting your combat score, the best possible agent role is suggested for you. \n\n"<<RESET;
            cout<<BG_RED<<"\n\t NOTE: The guide is purely based on ACS value and does not take into account player's personal preferences or playstyle. \n\t Players are encouraged to experiment with different agents to find the best fit for their individual playstyle.\n"<<RESET<<endl;

            if(scores>=300 && match_data[0]>=20 && match_data[5]>=5){

                cout<<YELLOW<<"\t\t >>> After taking a look on to your Dominating stats and computated combat score we suggest yo to go for";cout<<BG_RED<<" Duelists "<<RESET<<" role  ";
                cout<<YELLOW<<" Taking  a more deep look into your overall performance you should try to play"<<BG_RED<<"Jett, Yoru, Waylay, Neon , Reyna or Chamber too[Sentinel but your playstyle allows Chamber to be the duelist of the team as well]"<<RESET<<endl;
                cout<<"You can get more First bloods and kills with these duelists as they will allow you to get easy picks and escape safely with their mobility and evasive abilites easily,"<<endl;
            }
            else if(scores>=300 && match_data[0]>16 && match_data[2]>=5 && match_data[5]>3){


                cout<<YELLOW<<"\t\t >>> After taking a look on to your fabulous stats and computated combat score we suggest yo to go for";cout<<BG_RED<<" Duelists "<<RESET<<" role  ";
                cout<<YELLOW<<" Taking  a more deep look into your overall performance you should try to play"<<BG_RED<<"Pheonix, Iso, Raze or Yoru"<<RESET<<endl;
                cout<<BLUE<<"These duelists if paired with a supporting team can literaly dominate the battle fields, your no. of assists paired with high no. of kills and First Bloods shows that you have absolue potential to play as these Duelists and also assist your team for maximum impact. "<<endl;

            }

            else if(scores>=270  && match_data[0]>=15 && match_data[1]>=10 && match_data[2]>5 && match_data[5]>=3){

                cout<<YELLOW<<"\t\t >>> After taking a look on to your fabulous stats and computated combat score we suggest yo to go for";cout<<BG_RED<<"Initiators "<<RESET<<" role.  ";
                cout<<YELLOW<<" Taking  a more deep look into your overall performance you should try to play"<<BG_RED<<"Breach, Sova,Gekko, KAY/O,Skye,Fade, Tejo or even Waylay (If you can TP back before getting killed)."<<RESET<<endl;
                cout<<BLUE<<"\t\tThis Agent Category if paired with a supporting team can literaly help your team  dominate the battle fields and make it easy for your Duelists to take more successful entries, your no. of assists paired with high no. of kills and decent First Bloods shows that you have absolue potential to play as Initiators and also assist your team for maximum impact. "<<endl;

            }

            else if(scores>=250  && match_data[0]>10 && match_data[1]>10 && match_data[2]>=5 && match_data[5]>=4){

                cout<<YELLOW<<"\t\t >>> After taking a look on to your fabulous stats and computated combat score we suggest yo to go for";cout<<BG_BLUE<<"Contollers "<<RESET<<" role.  ";
                cout<<YELLOW<<" Taking  a more deep look into your overall performance you should try to play"<<BG_RED<<"Omen, harbour, Astra, Brimstone, Clove or Viper."<<RESET<<endl;
                cout<<BLUE<<"\t\tThis Agent Category if paired with a supporting team can literaly help your team  maintain control on the sites and make it easier to defuse or plant spikes. Smoke off or expected angles, block of enemies by  creating blind spots via smokes and when on sites just ensure to smoke all entry points or cut off angles so defending in all the situation becomes easy and tackable"<<endl;

                cout<<BLUE<<"\n\t\t >>>Also avoid taking on early fights your stats suggests you can be more handy to your team by playing a passive role, help your team to contain sites, this will elevate your gameplay by a good margin"<<endl;

            }

            else if(scores>=190  && match_data[0]>=10 && match_data[1]>15 && match_data[2]>=7 && match_data[5]<4){

                cout<<YELLOW<<"\t\t >>> After taking a look on to your fabulous stats and computated combat score we suggest yo to go for";cout<<BG_BLUE<<"Sentinels"<<RESET<<" role.  ";
                cout<<YELLOW<<" Taking  a more deep look into your overall performance you should try to play"<<BG_RED<<"Deadlock, Sage, Vyse, Veto, Chamber,Cypher, KillJoy."<<RESET<<endl;
                cout<<BLUE<<"\t\tThis Agent Category literaly help your team  fend off against lurkers and backstabbers. Post Plant enemies try to flock your team from all sides or even when ur team is fighting their way to plant, Lurkers from Mid or Backstabbers can cause troubles. Put your Traps in mids or possible corners . place them in such a way that they are in enemies blindspots but your enemies are clearly seen by them and alert you just in time so the team knows of threats sneaking onto them "<<endl;

                cout<<BLUE<<"\n\t\t >>>Also avoid taking on early fights your stats suggests you can be more handy to your team by playing a passive role, help your team to contain sites, this will elevate your gameplay by a good margin"<<endl;

            }
            else{

                cout<<YELLOW<<"\t\t >>> Your stats suggest that you need to work more on your gameplay to find a suitable agent role for yourself. Keep practicing and experimenting with different agents to find the best fit for your playstyle."<<RESET<<endl;
            }

        }



    };

    void displayStats(const vector<int>& Scores,const vector<string>& stat_names){
        
        string border(50,'=');
                    cout<<GREEN<<border<<RESET<<endl;
                    cout<<CYAN<<"\t\t>>> Your Match Stats <<<"<<RESET<<endl;
                    cout<<GREEN<<border<<RESET<<endl;
                    for(size_t  i = 0; i < Scores.size(); i++) {
                    Sleep(700);

                    cout << YELLOW << "\t\t" << stat_names[i] << " : ";

                    if(i == 0) { // Kills
                        if(Scores[0] >= Scores[1])
                            cout << GREEN << Scores[i];
                        else cout<<RED<<Scores[i];
                    }
                    else if(i == 1) { // Deaths
                        if(Scores[i]==0) cout<<YELLOW<<Scores[i]<<RESET;
                        else cout << RED << Scores[i];
                        
                    }
                    else if(i == 3) { // Round Wins
                        if(Scores[3] >= Scores[4])
                            cout << GREEN << Scores[3];
                        else
                            cout << RED << Scores[3];
                        }
                        else if(i == 4) { // Round Losses
                            if(Scores[i]==0) cout<<YELLOW<<Scores[i]<<RESET;
                            else cout << RED << Scores[i];
                        }
                    else{cout<<GREEN<<Scores[i];}  //Assists

                        cout << RESET << endl;
                    }
                    cout<<GREEN<<border<<RESET<<endl;

    }




    int main(){
    
        SetConsoleOutputCP(CP_UTF8);
        Agents GetStats; 
        string choice;
        string ch2,ch3;

        while(true){
            system("cls");
            GetStats.collect_data();
            vector<int> array = GetStats.data_array();

        
            
        
            cout<<CYAN<<"\t\t>>Do you confirm the above details? (yes/no): ";
            cin>>choice;

            if(choice=="yes"){
                cout<<BG_GREEN<<"\n\t>>> Data confirmed successfully! <<<"<<RESET<<endl;
                //vector<int> Scores=GetStats.data_array();

                cout<<YELLOW<<"\n\t\t>>>> Do you want to view your stats? (yes/no) : ";cin>>choice; 

                if(choice=="yes"){ //stats display starts here
                    system("cls");
                    cout<<CYAN<<"\n\t\t>>> Collecting data please wait->";
                    
                    Sleep(1000);
                    cout<<" ✅ "<<RESET<<endl;
                    Sleep(1000);
                    system("cls");
                    cout<<MAGENTA<<"\t\t Reading your stats for upload->";
                    Sleep(1000);
                    cout<<" ✅ "<<endl;
                    Sleep(1000);

                    Data :
                    system("cls");

                    displayStats(array,GetStats.get_TAGS());
                    cout<<MAGENTA<<"\n>>> Performance Analysis Graphical Representation : "<<RESET<<endl;
                        GetStats.Display_KD_Graph();
                        cout<<"\n"<<RESET<<endl;

                    while(true){

                    cout<<MAGENTA<<"\n>>>1. See Match  data\n>>>2.Re-enter Overall Match Statistics\n>>>3.View Your Combat Card\n>>>4.Exit Program\n>>>Enter valid choice option (1-3): ";cin>>ch2;
                    if(ch2=="1"){

                        goto Data;
                    }
                    if(ch2=="2"){
                        break;
                    }
                    else if(ch2=="3"){
                        system("cls");
                        cout<<MAGENTA<<"\n\t\t >>> Generating your Combat Card..... [Process: ";
                        Sleep(1500);
                        cout<<" ✅ ]"<<RESET<<endl;
                        Sleep(1000); system("cls");
                        cout<<MAGENTA<<"\n>>> Fetching final calculation.... [Process: ";
                        Sleep(1600);
                        cout<<" ✅ ]"<<RESET<<endl; Sleep(999); system("cls");
                        GetStats.PASS_KEY();
                        cout<<"\n\n";
                        GetStats.Agent_Guide();
                        cout<<"\n"<<RESET<<endl;
                        cout<<MAGENTA<<"\n>>> Press any key to return to main menu...."; cin>>ch3;
                        system("cls");
                    }
                    else if(ch2=="4"){
                        cout<<BG_RED<<"\n\t>>Program exited succefully. <<<"<<RESET<<endl; return 0;
                    }
                    
                    else{
                        system("cls");
                        cout<<BG_RED<<"\n\t\t>>> Invalid choice!! Enter valid option number from above. <<<"<<RESET<<endl;
                    }}
                
                }  //stats display ends here

                else if(choice=="no"){
                    cout<<BG_RED<<"\n\t>>> Exiting without stats display. <<<"<<RESET<<endl;
                    break;
                }

            }else if(choice=="no"){

                cout<<BG_RED<<"\n>>> Data not confirmed! Do you want to re-enter the data? (yes/no): ";
                cin>>choice;
                cout<<RESET<<endl;

                if(choice=="yes"){
                    system("cls");
                    
                }else{
                    cout<<BG_RED<<"\n>>> Exiting without saving data. <<<"<<RESET<<endl;
                    return 0;
                }
            }else{
                cout<<BG_RED<<"\n>>Invalid Choice! Enter valid choice option"<<RESET<<endl;
            }}
        return 0;
    }