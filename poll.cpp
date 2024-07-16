#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isValidPollString(string pollData);
string upperCasePollString(string pollData);
bool isValidStateForecast(string forecast);
bool isValidUppercaseStateCode(string stateCode);
bool isValidPartyResult(string partyResult);
int countSeats(string pollData, char party, int& seatCount);

int main()
{
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D,CA"));
    int seats;
    seats = -999;    // so we can detect whether countSeats sets seats
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
    seats = -999;    // so we can detect whether countSeats changes seats
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    assert(isValidPollString(""));
    assert(isValidPollString("ca"));
    assert(!isValidPollString("Va3b5k,Vt,mo4h6%45y"));
    assert(!isValidPollString("Va3b5k,Vt,mo4h6u45ya"));
    assert(!isValidPollString("Va3b5k,Vt,mo4h6u345y"));
    assert(!isValidPollString("3"));
    seats = -999;
    assert(countSeats("lm4c,CA3d4c", 'c', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats("CA5d, NY4d, VT", 'd', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats("lm4c,CA3d4c,", 'd', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats(",CA4c,CA3d4c,", 'd', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats("ln5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 1  &&  seats == -999);
    seats = -999;
    assert(countSeats("CT5D,NY9R16l1I,VT,ne3r00D", 'l', seats) == 0  &&  seats == 16);
    seats = -999;
    assert(countSeats("cT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
    cerr << "All tests succeeded" << endl;
}


// checks for valid poll string
bool isValidPollString(string pollData) {
  if (pollData == ""){
      return true;
    }
// calls upperCasePollString and capitalizes the poll data so that the stateforecast check will work right
  pollData = upperCasePollString(pollData);
// start checks for the beginning of the state forecast and i checks for the end of it
  int i = 0;
  int start = 0;
// checks to see if the string is valid by individually checking the state forecast from left to right
  while (i < pollData.size()) {
// iterates through the string and checks to see when there is a comma
    while (i < pollData.size() && pollData.at(i) != ',') {
      i++;
    }
      
// when it gets to the comma, it takes in the string from the beginning of the beginning of the position to right before the comma
      if(!isValidStateForecast(pollData.substr(start, i -start))) {
          return false;
      }
// it iterates i one more so that the position is past the comma
      i ++;
// sets the start position to i which is one past the comma now
      start = i;
  }
  return true;
}

// changes the string to upper case
string upperCasePollString(string pollData) {
// created a new string to alter the polldata
  string capString = "";
// for loop starts at the beginning of the string and takes in a character and uppercases it
// then capitalized the input and stores it into the string
  for (int i = 0; i < pollData.size(); i++) {
    char currChar = toupper(pollData[i]);
    capString += currChar;
  }
  return capString;
}

// here this is being called within isValidPollString which has already
// checks to see if the forecast is valid
bool isValidStateForecast(string forecast) {
// this doesnt really need to return false it could also return true, it doesnt matter. we just need this to make sure that this case doesn't enter the next if statement
  if (forecast == "") {
    return false;
  }
// this string is created to grab the first 2 letters of the forecast
  string firstTwoChars = forecast.substr(0, 2);
// checks to see if the state code is valid
  if (!isValidUppercaseStateCode(firstTwoChars)) {
// if state code is invalid the function returns false and exits the function
    return false;
  }

// now that we know that the first two characters are valid. we skip to the second position to the party results
  int start = 2;
// this takes the substring of the party result because when its not a digit its most likely a letter and thats when the party result ends
  for (int i = 2; i < forecast.size(); i++) {
// if the character is not a digit it goes through the if statement
    if (!isdigit(forecast.at(i))) {
      if (!isValidPartyResult(forecast.substr(start, i - start + 1)))
        return false;
      start = i + 1;
    }
  }
  return true;
}

// checks to see if the party result is valid
bool isValidPartyResult(string partyResult) {
// for the while loop
  int i = 0;
  int numDigits = 0;
// party result can be nothing but it doesnt work for this function
  if (partyResult == "") {
    return false;
  }
//  i am counting the amount of digits there are and putting it into an integer so i can compare it
  while (i < partyResult.size() && isdigit(partyResult.at(i))) {
    numDigits++;
    i++;
  }
// when the loop breaks i check to see if there is a valid amount of digits, returns falso if there is too little or many
  if (numDigits > 2 || numDigits == 0) {
    return false;
  }


// if i stops at the size that means we have just numbers and no letters
  if (i == partyResult.size()) {
    return false;
  }
// checks to see if the character at is is not a letter, if its not then its flase
  if (!isalpha(partyResult.at(i))) {
    return false;
  }
// if all these go through then the party result is valid
 return true;
}
// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode) {
  const string codes = "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
                       "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
                       "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
  return (stateCode.size() == 2 &&
          stateCode.find('.') == string::npos &&  // no '.' in stateCode
          codes.find(stateCode) != string::npos); // match found
}

int countSeats(string pollData, char party, int& seatCount) {
    
    party = toupper(party);
    pollData= upperCasePollString(pollData);
    if (!isValidPollString(pollData)){
        return 1;
    }
    if (!isalpha(party)){
        return 2;
    }
    int i = 2;
    int count = 0;
    int first = 0;
    int second = 0;
    while (i < pollData.size()){
        while (i < pollData.size() && pollData.at(i) != party) {
            i++;
        }
        
        if (isdigit(pollData.at(i - 1))){
            second = pollData.at(i - 1) - '0';
            if (isdigit(pollData.at(i - 2))) {
                first = (pollData.at(i - 2) - '0') * 10;
            }
            count += first + second;
            first = 0;
            i++;
        }
    }
    
    seatCount= count;
    return 0;
}
