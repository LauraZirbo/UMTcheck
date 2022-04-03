#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
ifstream f("input.txt");
ofstream g("output.txt");

void getData(string s, int& lc, int& uc, int& digits) {
	//I NEED GO THROUGH THE STRING ONCE TO KNOW WHAT CHANGES
	//TO MAKE IN ORDER TO MAKE AS FEW AS POSSIBLE
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			lc++;
		if (s[i] >= 'A' && s[i] <= 'Z')
			uc++;
		if (s[i] >= '0' && s[i] <= '9')
			digits++;
	}
}

int repetition(string& s, int& lc, int& uc, int& digits) {
	int nrOfChanges = 0;
	char a = s[0], b = s[1];
	char newChar;
	string newString1 = "", newString2 = "";
	int lenght;
	lenght = s.size();
	int ok;
	int i = 2;
	while (i < s.size())
	{
		ok = 0;
		if (s[i] == b)
		{
			if (s[i] == a)
			{
				//CHEKC IF WE ADD, DELETE OR SIMPLY CHANGE A CHARACTER, BASED ON THE NUMBER OF CHARACTERS ALREADY IN THE STRING 
				// ONE CHANGE WILL BE MADE
				nrOfChanges++;
				//IF THE STRING IS ALREADY TOO LONG WE DELETE THE REPEATING CHARACTER, THUS, POSSIBLY ELIMINATING ANOTHER ISSUE WITH THE PASSWORD
				if (lenght > 20)
				{
					lenght--;
					if (s[i] >= 'a' && s[i] <= 'z')
						lc--;
					if (s[i] >= 'A' && s[i] <= 'Z')
						uc--;
					if (s[i] >= '0' && s[i] <= '9')
						digits--;
					newString1 = s.substr(0, i);
					newString2 = s.substr(i + 1, s.size() - (i + 1));
					s = newString1 + newString2;
					//WE USE THE OK VALUE TO CHECK IF WE'VE DELETED A CHARACTER. IF SO, WE DON'T HAVE TO CHANGE a AND b AT THE END
					ok = 1;
				}
				else
				{
					//IF THE STRING IS TOO SHORT WE BREAK THE REPEATING SEQUENCE BY ADDING ANOTHER CHARACTER INBETWEEN
					if (lenght < 6)
					{
						lenght++;
						newString1 = s.substr(0, i);
						newString2 = s.substr(i, s.size() - i);
						char newChar = s[i] + 1;
						if (lc == 0)
						{
							//WE DON'T HAVE TO CHECK IF THE REPEATING CHARACTER IS A SINCE IF lc IS 0 IT CAN'T BE THE SAME CHARACTER
							newChar = 'a';
							lc++;
						}
						else {
							if (uc == 0) {
								//WE DON'T HAVE TO CHECK IF THE REPEATING CHARACTER IS A SINCE IF uc IS 0 IT CAN'T BE THE SAME CHARACTER
								newChar = 'A';
								uc++;
							}
							else
							{
								//IF WE GET TO THIS BRANCH WE MIGHT AS WELL ADD A DIGIT SINCE IN THE BEST CASE ADDING A DIGIT HELPS (digit == 0)
								// AND IN THE WORST CASE IT MAKES NO DIFFERENCE WHAT WE ADD
								if (s[i] != '1')
									newChar = '1';
								else
									newChar = '2';
								digits++;
							}
						}
						newString1.push_back(newChar);
						s = newString1 + newString2;
					}
					else
					{
						//IF THE LENGHT IS ALREADY GOOD, WE ONLY CHANE THE PASSWORD, TO PREVENT CREATING OTHER PROBLEMS
						//HERE WE CHECK TO SEE WHICH CHARACTER WOULD BE BEST TO CHANGE 
						if (s[i] >= 'a' && s[i] <= 'z')
						{
							if (digits == 0)
							{
								s[i] = '1';
								lc--;
								digits++;
							}
							else
							{
								if (uc == 0)
								{
									s[i] = 'A';
									uc++;
									lc--;
								}
								else
								{
									s[i] = 'A';
									uc++;
									lc--;
									//IT DOESN'T MATTER IN WHAT I CHANGE IT 
									//SINCE IT WE NOW KNOW THAT WE HAVE ALL
									//THE NECESARRY TYPES OF CHARACTERS
								}
							}
						}
						else {
							if (s[i] >= 'A' && s[i] <= 'Z')
							{
								if (digits == 0)
								{
									s[i] = '1';
									uc--;
									digits++;
								}
								else
								{
									if (lc == 0)
									{
										s[i] = 'a';
										lc++;
										uc--;
									}
									else
									{
										s[i] = '1';
										digits++;
										uc--;
										//IT DOESN'T MATTER IN WHAT I CHANGE IT 
										//SINCE IT WE NOW KNOW THAT WE HAVE ALL
										//THE NECESARRY TYPES OF CHARACTERS
									}
								}
							}
							else {
								if (s[i] >= '0' && s[i] <= '9')
								{
									if (lc == 0)
									{
										s[i] = 'a';
										digits--;
										lc++;
									}
									else
									{
										if (uc == 0)
										{
											s[i] = 'A';
											uc++;
											digits--;
										}
										else
										{
											s[i] = 'a';
											lc++;
											digits--;
											//IT DOESN'T MATTER IN WHAT I CHANGE IT 
											//SINCE IT WE NOW KNOW THAT WE HAVE ALL
											//THE NECESARRY TYPES OF CHARACTERS
										}
									}
								}
								else {
									if (lc == 0)
									{
										s[i] = 'a';
										lc++;
									}
									else
									{
										if (uc == 0)
										{
											s[i] = 'A';
											uc++;
										}
										else
										{
											s[i] = '1';
											digits++;
											//WE MIGH AS WELL CHANGE IT INTO A DIGIT SINCE IN THE BEST CASE IT HELPS AND IN THE WORST CASE IT DOESN'T MATTER 
										}
									}

								}
							}
						}

					}
				}

			}
		}
		//IF WE DELETED A CHARACTER WE DON'T HAVE TO CHANGE THESE TWO
		if (ok == 0)
		{
			a = b;
			b = s[i];
			i++;
		}

	}
	return nrOfChanges;
}

int lowerCase(string& s, int& lc, int& uc, int& digits)
{
	int nrOfChanges = 0;
	int lenght = s.size();
	if (lc == 0)
	{
		nrOfChanges++;
		if (lenght < 6)
		{
			//WE DON'T NEED TO CHECK FOR REPETITIONS SINCE WE KNOW THAT THERE ARE NO OTHER LOWERCASE CHARACTERS IN THE PASSWORD
			s.push_back('a');
			lenght++;
			lc++;
		}
		else
		{
			//TO CHANGE WE ARE SEARCHING FOR THE FIRST CHARACTER THAT OF WHICH'S TYPE IS FOUND MORE OFTEN THAN ONCE. SINCE I'VE ALREADY CHECKED FOR REPETITIONS I WON'T BE AFRAID TO DELETE 
			//IT SINCE OTHER THAN THE CASE OF THE STRING BEING TO LARGE (WITH WHICH I WILL DEAL WITH LATER ON) THE OTHER CHARACTERS WON'T VE DELETED
			int i = 0;
			while (i < lenght)
			{
				if (s[i] >= 'A' && s[i] <= 'Z')
				{
					if (uc > 1)
					{
						//WE CAN CHANGE IT IN THE LOWERCASE, WHICH WON'T CREATE ANY REPETITION PROBLEMS SINCE WE KNOW THAT THERE ARE NO OTHER LOWERCASE CHARATERS
						s[i] = s[i] + 32;
						uc--;
						lc++;
						return nrOfChanges;
					}
					//WE CAN'T CHANGE THIS LETTER SO WE DON'T HAVE TO RUN ANY OTHER TESTS ON IT
					else i++;
				}
				if (s[i] >= '0' && s[i] <= '9')
				{
					if (digits > 1)
					{
						//AGAIN WE CAN CHANGE IT INTO WHATEVER SINCE THERE WON'T BE ANY REPETITION PROBLEMS
						s[i] = 'a';
						digits--;
						lc++;
						return nrOfChanges;
					}
					else i++;
				}
				//IF WE'VE REACHED THIS PLACE OF THE CODE IT MEANS THAT IT IS NEITHER A LETTER NOR A DIGIT, THEREFORE IT IS NOT IMPORTANT AND WE CAN CHANGE IT
				s[i] = 'a';
				lc++;
				return nrOfChanges;
			}
		}
	}
	return nrOfChanges;
}

int upperCase(string& s, int& lc, int& uc, int& digits)
{
	int nrOfChanges = 0;
	int lenght = s.size();
	if (uc == 0)
	{
		nrOfChanges++;
		if (lenght < 6)
		{
			//WE DON'T NEED TO CHECK FOR REPETITIONS SINCE WE KNOW THAT THERE ARE NO OTHER UPPERCASE CHARACTERS IN THE PASSWORD
			s.push_back('A');
			lenght++;
			uc++;
		}
		else
		{
			//TO CHANGE WE ARE SEARCHING FOR THE FIRST CHARACTER THAT OF WHICH'S TYPE IS FOUND MORE OFTEN THAN ONCE. SINCE I'VE ALREADY CHECKED FOR REPETITIONS I WON'T BE AFRAID TO DELETE 
			//IT SINCE OTHER THAN THE CASE OF THE STRING BEING TO LARGE (WITH WHICH I WILL DEAL WITH LATER ON) THE OTHER CHARACTERS WON'T VE DELETED
			int i = 0;
			while (i < lenght)
			{
				if (s[i] >= 'a' && s[i] <= 'z')
				{
					if (uc > 1)
					{
						//WE CAN CHANGE IT IN THE 'A', WHICH WON'T CREATE ANY REPETITION PROBLEMS SINCE WE KNOW THAT THERE ARE NO OTHER UPPERCASE CHARATERS
						s[i] = 'A';
						uc++;
						lc--;
						return nrOfChanges;
					}
					//WE CAN'T CHANGE THIS LETTER SO WE DON'T HAVE TO RUN ANY OTHER TESTS ON IT
					else i++;
				}
				if (s[i] >= '0' && s[i] <= '9')
				{
					if (digits > 1)
					{
						//AGAIN WE CAN CHANGE IT INTO WHATEVER SINCE THERE WON'T BE ANY REPETITION PROBLEMS
						s[i] = 'A';
						digits--;
						uc++;
						return nrOfChanges;
					}
					else i++;
				}
				//IF WE'VE REACHED THIS PLACE OF THE CODE IT MEANS THAT IT IS NEITHER A LETTER NOR A DIGIT, THEREFORE IT IS NOT IMPORTANT AND WE CAN CHANGE IT
				s[i] = 'A';
				uc++;
				return nrOfChanges;
			}
		}
	}
	return nrOfChanges;
}



int checkDigits(string& s, int& lc, int& uc, int& digits)
{
	int nrOfChanges = 0;
	int lenght = s.size();
	if (digits == 0)
	{
		nrOfChanges++;
		if (lenght < 6)
		{
			s.push_back('1');
			lenght++;
			digits++;
		}
		else
		{
			//TO CHANGE WE ARE SEARCHING FOR THE FIRST CHARACTER THAT OF WHICH'S TYPE IS FOUND MORE OFTEN THAN ONCE. SINCE I'VE ALREADY CHECKED FOR REPETITIONS I WON'T BE AFRAID TO DELETE 
			//IT SINCE OTHER THAN THE CASE OF THE STRING BEING TO LARGE (WITH WHICH I WILL DEAL WITH LATER ON) THE OTHER CHARACTERS WON'T VE DELETED
			int i = 0;
			while (i < lenght)
			{
				if (s[i] >= 'A' && s[i] <= 'Z')
				{
					if (uc > 1)
					{
						//WE CAN CHANGE IT IN '1', WHICH WON'T CREATE ANY REPETITION PROBLEMS SINCE WE KNOW THAT THERE ARE NO OTHER DIGITS
						s[i] = '1';
						uc--;
						digits++;
						return nrOfChanges;
					}
					//WE CAN'T CHANGE THIS LETTER SO WE DON'T HAVE TO RUN ANY OTHER TESTS ON IT
					else i++;
				}
				if (s[i] >= 'a' && s[i] <= 'z')
				{
					if (lc > 1)
					{
						//AGAIN WE CAN CHANGE IT INTO WHATEVER SINCE THERE WON'T BE ANY REPETITION PROBLEMS
						s[i] = '1';
						digits++;
						lc--;
						return nrOfChanges;
					}
					else i++;
				}
				//IF WE'VE REACHED THIS PLACE OF THE CODE IT MEANS THAT IT IS NEITHER A LETTER NOR A DIGIT, THEREFORE IT IS NOT IMPORTANT AND WE CAN CHANGE IT
				s[i] = '1';
				lc++;
				return nrOfChanges;
			}
		}
	}
	return nrOfChanges;
}

int checkEnough(string& s, int& lc, int& uc, int& digits)
{
	int nrOfChanges = 0;
	int lenght = s.size();
	char newChar = s[s.size() - 1] + 1;
	while (lenght < 6)
	{
		//IF THE CHARACTER IS NIETHER SPACEBAR NOR ENDLINE WE KEEP CHANGING IT TO MAKE SURE WE DON'T CREATE A REPETITION
		if (int(newChar) != 9 && int(newChar) != 31) {
			s.push_back(newChar);
			lenght++;
			nrOfChanges++;
			newChar = newChar + 1;
		}
	}
	return nrOfChanges;
}

int checkTooMany(string& s, int& lc, int& uc, int& digits)
{
	int nrOfChanges = 0;
	int lenght = s.size();
	int i = lenght - 1;
	while (lenght > 20 && i >= 0)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			if (lc > 1)
			{
				//WE CAN DELETE IT, WHICH WON'T CREATE ANY PROBLEMS SINCE WE KNOW THAT THERE ARE OTHER LOWERCASE CHARATERS
				s.pop_back();
				lc--;
				nrOfChanges++;
				lenght--;
			}
			//WE CAN'T DELETE THIS LETTER SO WE DON'T HAVE TO RUN ANY OTHER TESTS ON IT
			i--;
		}
		else {

			if (s[i] >= 'A' && s[i] <= 'Z')
			{
				if (uc > 1)
				{
					//WE CAN DELETE IT, WHICH WON'T CREATE ANY PROBLEMS SINCE WE KNOW THAT THERE ARE OTHER UPPERCASE CHARATERS
					s.pop_back();
					uc--;
					nrOfChanges++;
					lenght--;
				}
				//WE CAN'T DELETE THIS LETTER SO WE DON'T HAVE TO RUN ANY OTHER TESTS ON IT
				i--;
			}
			else {

				if (s[i] >= '0' && s[i] <= '9')
				{
					if (digits > 1)
					{
						//WE CAN DELETE IT, WHICH WON'T CREATE ANY PROBLEMS SINCE WE KNOW THAT THERE ARE OTHER UPPERCASE CHARATERS
						s.pop_back();
						digits--;
						nrOfChanges++;
						lenght--;
					}
					i--;
				}
				else {
					//IF WE'VE REACHED THIS PLACE OF THE CODE IT MEANS THAT IT IS NEITHER A LETTER NOR A DIGIT, THEREFORE IT IS NOT IMPORTANT AND WE CAN DELETE IT
					s.pop_back();
					nrOfChanges++;
					lenght--;
				}

			}
		}
	}
	return nrOfChanges;
}




int main()
//	LOOK AGAIN AT THE REPETITIONCASE SO THAT IT CHANGES IT IN A NUMBER WHEN IT SHOULD 
{
	int lc = 0, uc = 0, digits = 0, nrOfChanges = 0;
	string s;
	f >> s;
	getData(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + repetition(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + lowerCase(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + upperCase(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + checkDigits(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + checkEnough(s, lc, uc, digits);
	nrOfChanges = nrOfChanges + checkTooMany(s, lc, uc, digits);
	g << "The minimum number of changes that need to be made are: " << nrOfChanges << endl;
	g << "A sugestion which has had these changes made is: " << s;
	f.close();
	g.close();
	return 0;
}