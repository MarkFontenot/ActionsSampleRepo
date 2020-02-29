//
// Created by Jonathan Ebrahimian on 2/27/20.
//
#include <iostream>
#include "DSString.h"
#include "Indexer.h"
#include "DSVector.h"
#include <fstream>

/*IndexBook
 * This method takes a book and a key word list and indexes the
 * passed in book for the key words. It creates an output file
 * with the key words and the pages they appeared on.
 *
 * Return: void
 */
void Indexer::indexBook(char * keyWordsFileName, char * bookFileName,char * outputFileName) {
    char part [500];//buffer

    //gets keywords
    DSVector<DSString> keyWords;
    keyWords = getKeyWords(keyWordsFileName,part);

    //gets a vector of all pages
    DSVector<DSString> rawPages;
    rawPages = getEachPage(bookFileName,part);

    //gets a vector of each page each keyword appears in
    DSVector<DSString> pagesAppeared;
    pagesAppeared = getPagesForEachWord(keyWords,rawPages);

    //sorts and writes the vector created above to an output file
    writeToOutputFile(outputFileName,keyWords,pagesAppeared);
}

/* AddPageNumbers
 * This method adds page numbers and formats raw .txt files passed
 * in to fit the project requirements. (Only used for testing purposes)
 *
 * Return: void
 */
void Indexer::addPageNumbers(char * rawBookFileName,char * bookInputFileName){
    //open book
    ifstream rawBook;
    rawBook.open(rawBookFileName);
    if(!rawBook){
        cout << "File did not open" << endl;
        exit(1);
    }
    char part [100];
    //open output fil
    ofstream finalBook;
    finalBook.open(bookInputFileName);

    int counter = 0;
    int pageNumber = 2;

    //add initial 1
    finalBook << "<";
    finalBook << 1;
    finalBook << "> " << endl;
    while(!rawBook.eof()){
        //write each line to the output file
        rawBook.getline(part,500,'\n');
        finalBook << part << endl;
        counter++;

        //every 10 lines add a page break
        if(counter == 10){
            finalBook << endl;
            finalBook << "<";
            finalBook << pageNumber;
            finalBook << ">" << endl;
            cout << pageNumber << endl;
            pageNumber++;
            counter = 0;
        }
    }
    //add final page indicator
    finalBook << endl;
    finalBook << "<";
    finalBook << -1;
    finalBook << ">";
    finalBook.close();
    rawBook.close();
}


/*GetKeyWords
 * This method gets the name of a file and creates a DSVector of DSStrings
 * containing each keyword.
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getKeyWords(char * keyWordFileName, char part []){
    //opens keyword file
    ifstream keyWordsFile;
    keyWordsFile.open(keyWordFileName);
    if(!keyWordsFile){
        cout << "Error opening input file key words";
        exit(1);
    }

    DSVector<DSString> keyWords;
    DSString temp;
    char * pch;

    //removes all elements in separator
    char  separator [] = ".?!:',;\"/\\[]{}\n";

    //iterates through keyword file
    while(!keyWordsFile.eof()){
        keyWordsFile.getline(part,500,'\n');//gets a line from keyword file
        pch = strtok(part,separator);//removes special chars
        while (pch != NULL){
            temp = temp + pch;
            pch = strtok(NULL, separator);
        }
        temp.lowercase();//makes keywords lowercase

        //adds keyword to the vector if unique
        if(!keyWords.find(temp)){
            keyWords.append(temp);
        }
        temp = "";//resets temp variable
    }
    keyWordsFile.close();//close file
    return keyWords;
}

/* GetEachPage
 * This method seperates each page of the book into its own DSString and returns
 * a vector of DSStrings with all pages
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getEachPage(char * bookFileName, char part []){
    //open book file
    ifstream book;
    book.open(bookFileName);
    if(!book){
        cout << "Error opening input file book";
        exit(1);
    }
    DSVector<DSString> rawPages;
    DSString input;
    DSString pageAt;
    DSString content;
    bool first = true;
    bool add;
    char * pch;
    char  separator [] = " .?\"\t!:/\\[]{},;\n";

    //iterates through book file until <-1> is found
    while(!(input == (char *)"<-1>")){
        book.getline(part, 500, '\n');
        add = true;
        input = part;

        //checks if new line has correct angle bracket format and is not the first iteration
        if(input[0] == '<' && input[input.getLength() -1] == '>' && !first) {
            //checks if contents of angle brackets is a number
            pageAt = input.substring(1,input.getLength() -1);
            if(pageAt.isNum()){
                content = content.remove((char *)"'");//removes ' without adding spaces
                rawPages.append(content);
                add = false;//doesnt add the current string to the next element
                content = input + (char *)" ";//resets DSString for the next element
            }
        }
        //adds line to DSString and removes special chars and white space
        if(add){
            first = false;
            pch = strtok(part,separator);
            while (pch != NULL){
                content = content + pch + (char *)" ";//adds spaces between each separation
                pch = strtok(NULL, separator);
            }
        }
    }
    book.close();//close file
    return rawPages;
}

/* GetPagesForEachWord
 * Finds each page that each keyword is on and puts it into a DSString and
 * returns a DSVector containing those DSStrings.
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getPagesForEachWord(DSVector<DSString> & keyWords, DSVector<DSString> & rawPages){
    DSVector<DSString> pagesAppeared;
    DSString allPageNumbers;
    DSString endBracket((char *)">");
    DSString pageContents;
    DSString keyWordTemp;
    DSString space((char *)" ");
    DSString pageNumber;

    keyWords.sort();//sort keywords

    //initialize pagesAppeared DSVector
    for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append((char *)"-1");
    }

    //iterate through each page and check if a key word exists in the page
    for(int x = 0; x < rawPages.getSize(); x++){
        //get the current page and lowercase it
        pageContents = rawPages[x];
        pageContents.lowercase();
        for(int j = 0; j < keyWords.getSize(); j++){
            //lowercase and surround key word with spaces
            keyWordTemp = space + keyWords[j] + space;
            keyWordTemp.lowercase();

            //check if current page contains the keyword
            if(pageContents.contains(keyWordTemp) != -1){

                //get the page number of the page
                int lastIndex = pageContents.contains(endBracket);
                pageNumber = pageContents.substring(1,lastIndex);

                //add the new page to pagesAppeared DSVector
                allPageNumbers = pagesAppeared[j];
                if(allPageNumbers == (char *)"-1"){
                    pagesAppeared.edit(pageNumber,j);//override -1 if first page found
                } else{
                    allPageNumbers = allPageNumbers + (char *)", " + pageNumber;
                    pagesAppeared.edit(allPageNumbers,j);
                }
            }
        }
    }
    return pagesAppeared;
}



/* WriteToOutputFile
 * This method takes the key words and the vector containing the info
 * of where each word appears. It sorts the pages where each word appears
 * and writes them to the output file and wraps whenever a line length is
 * more than 70.
 *
 * Return: void
 */
void Indexer::writeToOutputFile(char * fileOutputName, DSVector<DSString>& keyWords, DSVector<DSString>& pagesAppeared){
    DSString pageNumbers;
    char currLetter;
    char nextLetter;
    DSVector<DSString> result;
    DSVector<int> intResults;
    int lengthOfLine = 0;

    //opening output file
    ofstream fout;
    fout.open(fileOutputName);
    if(!fout.is_open()){
        cout << "Error opening output file" << endl;
        exit(1);
    }
    //iterates through each key word
    for(int j = 0; j < keyWords.getSize(); j++) {
        pageNumbers = pagesAppeared[j];

        //checks if the word was found on any page
        if(!(pageNumbers == (char *)"-1")){
            //adds keyword and character index to output file
            addWordToOutputFile(keyWords[j],lengthOfLine,nextLetter,currLetter,fout);
            result = pageNumbers.split((char *)", ");//splits string containing page numbers
            intResults = getIntDSVector(result);//converts DSVector of DSStrings to DSVector of ints

            //iterates through each page in the int DSVector
            bool start = true;
            for(int x = 0; x < intResults.getSize();x++){
                pageNumbers = intResults[x];
                addPageToOutputFile(pageNumbers,lengthOfLine,start,fout);
            }
            fout << endl;//new line for new word
        }
        lengthOfLine = 0;//resets line length
    }
    fout.close();//close file
}

/* addWordToOutputFile
 * This method adds a word passed in to the output file and
 * checks if the first letter of the passed in word is different
 * than the previous word.
 *
 * Return: void
 */
void Indexer::addWordToOutputFile(DSString word, int & lengthOfLine, char & nextLetter, char & currLetter, ofstream & fout) {
    nextLetter = word[0];//gets first letter of word

    //checks if first letter of word is new
    if(currLetter != nextLetter){
        currLetter = nextLetter;
        nextLetter = toupper(nextLetter);
        fout << "[" << nextLetter << "]" << endl;//adds new letter to index
    }
    lengthOfLine += word.getLength() + 2;
    fout << word << ": ";//adds word to output file
}

/* getIntDSVector
 * Converts a DSVevtor containing DSStrings that are numbers to a
 * DSVector containing integers and sorts the vector.
 *
 * Return: DSVector<int>
 */
DSVector<int> Indexer::getIntDSVector(DSVector<DSString> & result) {
    DSVector<int> intResults;
    DSString tempString;

    //iterates through results and changes DSString to int
    for(int x = 0; x < result.getSize();x++){
        tempString = result[x];
        intResults.append(tempString.getInt());
    }
    intResults.sort();//sorts int vector from low to high
    return intResults;
}

/* AddPageToOutputFile
 * Adds the word passed in to the output file. Adds commas between numbers.
 * Wraps text at 69 chars per line. (Instructions said "The line should wrap before 70 characters")
 *
 * Return: void
 */
void Indexer::addPageToOutputFile(DSString page, int & lengthOfLine,bool& start, ofstream & fout) {
    //doesn't add , if first page being added
    if(start){
        //new line if the key word + the page length > 69
        if(lengthOfLine + page.getLength() > 69){
            fout << endl << "    " << page;
            lengthOfLine = 4 + page.getLength();
        }else{
            fout << page;
            lengthOfLine += page.getLength();
        }
        start = false;
    }else {
        //checks if line needs to wrap
        if(lengthOfLine + page.getLength() + 3 > 69){
            fout << "," << endl << "    ";
            lengthOfLine = 4;
        }else{
            fout << ", ";
            lengthOfLine += 2;
        }
        //adds page to line length and output file
        lengthOfLine += page.getLength();
        fout << page;
    }
}



