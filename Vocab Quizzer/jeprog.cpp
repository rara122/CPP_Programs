#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

int listCreator(int, int);
int vocabQuiz(int);
int putGrade(int, int, string);
int dailyGrade();
int avgGrade();
int viewList(int);
bool fileExists(const char *fileName);
bool is_number(const std::string& s);
int checkInput (string s);


int main(){
  int option = 0;

  while (option != 4){
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
       << "Option 1: Vocab List Creator\nOption 2: Vocab Quiz\n"
       << "Option 3: Statistics\nOption 4: End\n"
       << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\nSelect Option: #";
  cin >> option;

  if(option == 1){
    //VOCABULARY LIST CREATOR
    int i,j;
    string number = "badinput";
    cout <<"::Vocabulary List Creator::\n";
    while (checkInput(number)==-1){
      cout <<"User Please insert List name(Must be a number): ";
      cin >> number;
      }
    i = atoi(number.c_str());
    string filenamecheck;
    ostringstream sst;
    sst << i << ".txt";
    filenamecheck = sst.str();
    number = "null";

    //Check if file exists already
    while(fileExists(filenamecheck.c_str()) != 0){
      cout << "Already Exists Reenter List number: ";
      cin >> number;
      while (checkInput(number)==-1){
        cout << "Bad Input: Reenter List number: ";
        cin >> number;
        }

      i = atoi(number.c_str());
      sst.str("");
      sst << i << ".txt";
      filenamecheck = sst.str();
      }

    cout <<"User Please insert Number of items in the list: ";
    cin >> j;
    listCreator(i, j);
    }


  else if(option == 2){
    //VOCABULARY QUIZ
    int i = 0;
    string number = "badinput";
    cout <<"::Vocabulary Quiz::\n";
    cout <<"User Please input List number to be tested: ";
    //cin >> i;
    cin >> number;
    while (checkInput(number)==-1){
      cout << "Bad Input: Reenter List number to be tested: ";
      cin >> number;
      }
    i = atoi(number.c_str());
    while (vocabQuiz(i) == -1){
      cout << "File did not open, Input another List number: ";
      cin >> i;
      }
    }


  else if(option == 3){
    //STATISTICS
    int i;
    cout << "::Statistics::\n";
    cout << "1. Daily Grades(past 5 grades)\n"
      << "2. Total Grade\n3. List View\n\nChoose an Option: ";
    cin >> i;
    if(i == 1)
      dailyGrade();
    else if(i == 2)
      avgGrade();
	else if(i == 3){
	  cout << "Choose File to view: ";
	  cin >> i;
	  string filenamecheck;
      ostringstream sst;
      sst << i << ".txt";
      filenamecheck = sst.str();
      while(fileExists(filenamecheck.c_str()) == 0){
        cout << "Does Not Exist Reenter List number to be viewed: ";
        cin >> i;
        sst.str("");
        sst << i << ".txt";
        filenamecheck = sst.str();
        }
	  viewList(i);
	  }
    else
      ;
    }


  else if(option == 4){
    //END PROGRAM
    cout << "Exiting Program.\n";
    }
  else;

  }//END WHILE


return 0;
}




int listCreator(int num, int lnum){
ofstream fout;
ostringstream ss;
ss << num << ".txt";
string fname = ss.str();

fout.open (fname.c_str());
if(fout.is_open()){
  cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << fname << " being written to.\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
  string gword, eword;
  fout << lnum << "\n";
  for(int i=0; i<lnum; i++){
    cout << "User Please type German word: ";
    cin >> gword;
    cout << "User Please type English Translation: ";
    cin >> eword;
    fout << gword << "\n";
    fout << eword << "\n";
    cout << "\n";
    }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "Added " << lnum << " words to the file: "
    << fname << ".\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  fout.close();
  return 0;
  }
else{
  cout << "failed to open\n";
  return -1;
  }
}

int vocabQuiz(int num){
ifstream fin;
ostringstream ss;
ss << num << ".txt";
string fname = ss.str();

fin.open (fname.c_str());
if(fin.is_open()){
  cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout <<"Using File: " << fname << "\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~\n\n";
  int iterations, correct;
  string j, line, input;
  correct = 0;
  getline (fin, j);
  iterations = atoi(j.c_str());
  char c;

  for(int i=0; i<iterations; i++){
    getline (fin, line);
    cout << i+1 << ". " << line << " = ";
    getline (fin, line);
    cin >> input;
	for(int i=0; i < ((int)strlen(line.c_str())); i++){
      c = line[i];
      line[i] = (toupper(c));
      }

    for(int i=0; i < ((int)strlen(line.c_str())); i++){
      c = input[i];
      input[i] = (toupper(c));
      }

    if(strlen(line.c_str()) == strlen(input.c_str())){
      if(strcmp(line.c_str(), input.c_str()) == 0){
        correct++;
        cout << "User that is correct =D\n";
        }
      else{
        cout << "User that is False =o\n";
        }
      }
    else{
      cout << "User that is False =o\n";
    }
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout << "Congratulations User You scored " << correct
    << "/" << iterations << " correct!!!\n\n";
  fin.close();
  putGrade(correct, iterations, fname);
  return 0;
  }
else
  return -1;

}


int putGrade(int cor, int tot, string lname){
ofstream faccess;
faccess.open("Statistics.txt", ios::app);
if(faccess.is_open()){
  time_t now = time(0);
  char* dt = ctime(&now);
  faccess << "~~~~~~~~~~~~~~~~~~~~~~~~\n" << dt << "File: "
    << lname << "\nScore: " << cor << "/" << tot
    << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
  faccess.close();
  return 0;
  }
else{
  cout << "File, Statistics.txt did NOT open\n";
  return -1;
  }
}

int dailyGrade(){
ifstream fin;
fin.open("Statistics.txt");
string word;
string day;
string days[6];
while (!fin.eof()){
  fin >> word;
  if(word == "Mon"){
    cout << "~~~~~~~~~~~~~~~\nMon\n";
    getline(fin, word);
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Sun";
    days[1] = "Sat";
    days[2] = "Fri";
    days[3] = "Thu";
    days[4] = "Wed";
    days[5] = "Tue";
    day = "Mon";
    break;
    }
  else if(word == "Tue"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nTue\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Mon";
    days[1] = "Sun";
    days[2] = "Sat";
    days[3] = "Fri";
    days[4] = "Thu";
    days[5] = "Wed";
    day = "Tue";
    break;
    }
  else if(word == "Wed"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nWed\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Tue";
    days[1] = "Mon";
    days[2] = "Sun";
    days[3] = "Sat";
    days[4] = "Fri";
    days[5] = "Thu";
    day = "Wed";
    break;
    }
  else if(word == "Thu"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nThu\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Wed";
    days[1] = "Tue";
    days[2] = "Mon";
    days[3] = "Sun";
    days[4] = "Sat";
    days[5] = "Fri";
    day = "Thu";
    break;
    }
  else if(word == "Fri"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nFri\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Thu";
    days[1] = "Wed";
    days[2] = "Tue";
    days[3] = "Mon";
    days[4] = "Sun";
    days[5] = "Sat";
    day = "Fri";
    break;
    }
  else if(word == "Sat"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nSat\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Fri";
    days[1] = "Thu";
    days[2] = "Wed";
    days[3] = "Tue";
    days[4] = "Mon";
    days[5] = "Sun";
    day = "Sat";
    break;
    }
  else if(word == "Sun"){
    getline(fin, word);
    cout << "~~~~~~~~~~~~~~~\nSun\n";
    for(int i=0; i<2; i++){
      getline(fin, word);
      cout << word << "\n";
      }
    days[0] = "Sat";
    days[1] = "Fri";
    days[2] = "Thu";
    days[3] = "Wed";
    days[4] = "Tue";
    days[5] = "Mon";
    day = "Sun";
    break;
    }
  else;
  }//ENDWHILE

  for(int i=0; i<4; i++){
    while(!fin.eof()){
      fin >> word;
      if(((word == "Mon")|(word == "Tue")|(word == "Wed")|
       (word == "Thu")|(word == "Fri")|(word == "Sat")|
       (word == "Sun"))&& word != day){
        cout << "~~~~~~~~~~~~~~\n";
        cout << word << "\n";
        getline(fin, word);
        for(int i=0; i<2; i++){
          getline(fin, word);
          cout << word << "\n";
          }
        }
      }
    }
  cout << "~~~~~~~~~~~~~~\n";
  fin.close();
/*  for(int i=0; i<6; i++){
    while(!fin.eof()){
      fin >> word;
      if(days[i] == word){
        cout << word << "\n";
        getline(fin, word);
        for(int i=0; i<2; i++){
          getline(fin, word);
          cout << word << "\n";
          }
        }
      }
    }
*/
return 0;
}


int avgGrade(){
  ifstream fin;
  fin.open("Statistics.txt");
  string scorefind;
  double num, tnum, sum, tsum, count;
  char c;
  sum = 0.0;
  tsum = 0.0;
  count = 0.0;
  if(fin.is_open()){
    while(!fin.eof()){
      fin >> scorefind;
      if(scorefind == "Score:"){
        fin >> num;
        fin >> c;
        fin >> tnum;
        sum += num;
        tsum += tnum;
        count++;
        }
      }
    }
  num = sum/count;
  tnum = tsum/count;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~\nAverage is about " << setprecision(2)
    << fixed << num << "/" << tnum << ".\nPercent: ~ " << num/tnum * 100
    << "%\n~~~~~~~~~~~~~~~~~~~~~~~\n";

  fin.close();
  return 0;
}

bool fileExists(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

int viewList(int num){
  string fname;
     ostringstream ss;
      ss << num << ".txt";
      fname = ss.str();

	ifstream fin;
    fin.open(fname.c_str());
	string word;
	int i = 1;
	fin >> word;
	while(fin >> word){
		cout << i << ". " << word << " = ";
		fin >> word; 
		cout << word << ".\n";
		i++;
	}

	return 0;
}



bool is_number(const std::string& s){
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int checkInput (string s){
// Return -1 if input is bad
// Return a valid positive int if good
  bool works = false;
  works = is_number(s);
  if (works) return atoi(s.c_str());
  else return -1;
}
