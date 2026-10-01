

**Project: Markov Chain Text Generator**

*Step-by-Step Instructions*

**Overview**

In this project, you will build a program that reads text from a file, learns the patterns of which words follow which, and then generates new text based on those patterns. This technique is called a Markov chain.

Your program will ask for the input filename, the order of the Markov chain (1, 2, or 3), and a maximum number of output words. It generates up to that many words and stops early if the current prefix has no successor.

**How to use this document**

1. Read the section below about what a Markov chain is.  
2. Skim the Required Functions section to get a sense of what code you will need to write.  
3. Follow the step-by-step instructions in the "**Step-by-Step Implementation Guide**"

**What is a Markov Chain?**

A Markov chain is a system that predicts what comes next by looking only at what just happened. For text, this means: given the current word (or words), what word is likely to follow?

The idea is to analyze real text and record patterns. If we read a whole book, we can count how often each word follows each other word. Then we use those patterns to generate new text that "sounds like" the original.

**Worked Example: Building a Markov Chain (Order 1\)**

Let's say our training text is this paragraph from a children's story:

*"The cat sat on the mat. The cat saw the dog. The dog ran away. The cat sat down."*

We scan through this text word by word and record what follows each word. We store this as pairs: a "prefix" (the current word) and a "suffix" (the word that came after it). With order 1, each prefix is a single word.

Position 1:  prefix \= "The"    suffix \= "cat"

Position 2:  prefix \= "cat"    suffix \= "sat"

Position 3:  prefix \= "sat"    suffix \= "on"

Position 4:  prefix \= "on"     suffix \= "the"

Position 5:  prefix \= "the"    suffix \= "mat."

Position 6:  prefix \= "mat."   suffix \= "The"

Position 7:  prefix \= "The"    suffix \= "cat"

Position 8:  prefix \= "cat"    suffix \= "saw"

Position 9:  prefix \= "saw"    suffix \= "the"

Position 10: prefix \= "the"    suffix \= "dog."

Position 11: prefix \= "dog."   suffix \= "The"

Position 12: prefix \= "The"    suffix \= "dog"

Position 13: prefix \= "dog"    suffix \= "ran"

Position 14: prefix \= "ran"    suffix \= "away."

Position 15: prefix \= "away."  suffix \= "The"

Position 16: prefix \= "The"    suffix \= "cat"

Position 17: prefix \= "cat"    suffix \= "sat"

Position 18: prefix \= "sat"    suffix \= "down."

Notice that we store every occurrence, including duplicates. Let's group them to see the patterns:

"The"  → \["cat", "cat", "dog", "cat"\]  (75% chance of "cat", 25% chance of "dog")

"cat"  → \["sat", "saw", "sat"\]         (67% chance of "sat", 33% chance of "saw")

"sat"  → \["on", "down."\]               (50/50)

"the"  → \["mat.", "dog."\]              (50/50)

The duplicates are what give us probability\! When we randomly pick from "The"'s list, we're 3x more likely to get "cat" than "dog" because "cat" appears 3 times.

**Generating Text from the Chain**

To generate new text, we "walk" the chain:

1\. Start with a word, say "The".

2\. Find all entries where prefix \= "The". We have four: \["cat", "cat", "dog", "cat"\].

3\. Randomly pick one. Let's say we get "cat" (75% likely).

4\. Now our current word is "cat". Find all entries where prefix \= "cat": \["sat", "saw", "sat"\].

5\. Randomly pick one. Let's say we get "saw" (33% likely).

6\. Now our current word is "saw". Find entries: \["the"\].

7\. Only one choice, so we get "the".

8\. Now look up "the": \["mat.", "dog."\]. Say we pick "dog."

9\. Continue until the requested maximum is reached or the current prefix has no successor.

Possible generated output: *"The cat saw the dog. The cat sat down."*

This sequence of sentences did not appear contiguously in the training text. Every adjacent word pair did appear there. A Markov generator can recombine observed transitions; it cannot invent an unobserved transition.

**Understanding the "Order" Parameter**

The **order** (also called "prefix length" or "state size") controls how many words the chain looks at when predicting the next word.

**Order 1:**

The chain looks at only the previous 1 word to decide what comes next.

Example: If the current word is "the", we look up all words that ever followed "the" in our training text.

Result: More random and chaotic output. Grammatically awkward but very "creative."

**Order 2:**

The chain looks at the previous 2 words together.

Example: If the current words are "the cat", we look up all words that ever followed "the cat" together.

Result: Often more local context than order 1, although the quality depends on the training text.

**Order 3 or higher:**

The chain looks at 3+ previous words.

Example: If the current words are "the cat sat", we look up what followed that exact phrase.

Result: Very coherent output, but often just reproduces chunks of the original text verbatim.

**The tradeoff:** Lower order \= more random. Higher order \= more similar to the original. For this project, your program should support orders 1, 2, and 3\.

**Worked Example: Order 1 vs Order 2**

Let's see how order affects the chain with a longer text. Consider this training text:

*"I went to the store. I went to the park. I walked to the store. She went to the movies."*

**With Order 1 (single-word prefixes):**

Key entries from the chain:

"I"       → \["went", "went", "walked"\]

"went"    → \["to", "to", "to"\]

"to"      → \["the", "the", "the", "the"\]

"the"     → \["store.", "park.", "store.", "movies."\]

"walked"  → \["to"\]

With order 1, the chain loses important context. Notice that "the" can lead to "store.", "park.", or "movies." – but the chain doesn't remember WHO went or HOW they got there. We might generate:

Possible output: "She went to the park. I went to the movies."

Neither "She went to the park." nor "I went to the movies." appeared as a complete sentence in the training text. Every adjacent pair in this output did appear. "She walked" is impossible here, even with order 1, because "She" was followed only by "went".

**With Order 2 (two-word prefixes):**

Now each prefix is TWO words joined together:

"I went"        → \["to", "to"\]

"went to"       → \["the", "the", "the"\]

"to the"        → \["store.", "park.", "store.", "movies."\]

"I walked"      → \["to"\]

"walked to"     → \["the"\]

"She went"      → \["to"\]

"the store."    → \["I", "She"\]

"the park."     → \["I"\]

Order 2 keeps two words of context. "I went" and "She went" are separate prefixes, both followed by "to". Once the current prefix is "to the", either path can choose any recorded successor of "to the". The model does not remember the subject from earlier in the sentence.

Possible output: *"I went to the park. I walked to the store. She went to the movies."*

Every three-word window must have appeared in the training text. Whole sentences need not have appeared. For example, "She went to the park." is possible with order 2: "She went" leads to "to", "went to" leads to "the", and "to the" can lead to "park.". "She walked" is impossible in this example at either order.

Higher order retains more local context and may repeat longer portions of the source. Lower order allows more recombination. Compare orders 1, 2, and 3 using the same training text; no order guarantees grammatical or novel output.

**What is a Header File?**

For this project, the header file (.h) contains function declarations: each declaration tells the compiler the function name, parameter types, and return type. The implementations belong in markov.cpp. Headers can contain other kinds of C++ definitions, but ordinary non-inline function bodies do not belong in this project's header.

When you write a program across multiple .cpp files, the compiler processes each file separately. If main.cpp wants to call a function defined in markov.cpp, the compiler needs to know that function exists – what it's called, what parameters it takes, and what it returns. The header file provides this information.

**What are Include Guards?**

A header may be included more than once while one .cpp file is processed, either directly or through another header. Repeating a compatible function declaration is legal. Other repeated header contents, such as a class definition, can cause a redefinition error.

Include guards make the preprocessor process the guarded contents only once within each translation unit (one .cpp file together with its included headers). Use this pattern:

\#ifndef MARKOV\_H

\#define MARKOV\_H

\#include \<string\>

// Your declarations go here

\#endif

Here's how it works:

\#ifndef MARKOV\_H means "if MARKOV\_H is NOT defined, continue."

\#define MARKOV\_H defines MARKOV\_H so it now exists.

\#endif marks the end of the conditional section.

The first inclusion defines MARKOV\_H and processes the header. Later inclusions while compiling that same .cpp file skip the guarded contents. Each .cpp file is compiled separately, so the guard does not prevent duplicate function definitions across different .cpp files. Put each ordinary function definition in markov.cpp only.

*The name (MARKOV\_H) can be anything, but by convention we use the filename in ALL\_CAPS with underscores. Always include guards in every header file you write\!*

**Required File Structure**

Your project must be organized into three files:

**main.cpp** – Contains main(), handles user input/output, and calls your Markov functions.

**markov.h** – Contains the six function declarations and includes \<string\> inside its include guard so std::string is declared even when this header is included first.

**markov.cpp** – Contains the function definitions (implementations).

Compile with: g++ \-std=c++11 \-Wall \-Wextra \-pedantic main.cpp markov.cpp \-o markov

**Required Functions**

Declare all six functions below in markov.h, inside its include guard and after \#include \<string\>. Implement them in markov.cpp. Include each library header in the file that uses it; for example, \<fstream\> for file reading and \<cstdlib\> for rand in markov.cpp. The outlines use short names such as string and rand; qualify them with std:: in your code, or use the using directive taught in class.

**Function 1: joinWords (helper)**

std::string joinWords(const std::string words\[\], int startIndex, int count);

**What it does:** This helper function takes several words from an array and glues them together into one string with spaces between them. You'll use this to create prefixes when order \> 1\.

**Parameters explained:**

words\[\] – The array of words to pull from.

startIndex – Which position to start from.

count – How many words to join together.

**Returns:** A single string with the words joined by spaces. The caller must supply a nonnegative startIndex and count whose entire range is within the array. A count of 0 returns an empty string.

**How to implement it:**

1\. Create an empty result string.

2\. Loop from i \= 0 to count \- 1:

   \- Add words\[startIndex \+ i\] to result

   \- If this isn't the last word, also add a space

3\. Return result.

**Example:**

If words \= \["the", "cat", "sat", "down"\]

joinWords(words, 0, 2\) returns "the cat"

joinWords(words, 1, 2\) returns "cat sat"

joinWords(words, 1, 3\) returns "cat sat down"

**Function 2: readWordsFromFile**

int readWordsFromFile(std::string filename, std::string words\[\], int maxWords);

**What it does:** Opens a text file and reads whitespace-separated words into the array, stopping at maxWords. Punctuation and capitalization stay attached to the words. Additional words beyond the capacity are not used.

**Parameters explained:**

filename – The name of the file to read (like "alice.txt").

words\[\] – An empty array that you will fill with words from the file.

maxWords – The maximum number of words the array can hold. Stop reading if you hit this limit.

**Returns:** The number of words actually read (0 for an empty or whitespace-only file). If the file cannot be opened, return \-1. A nonpositive capacity permits no array writes.

**How to implement it:**

1\. Create an ifstream object and open the file.

2\. Check if the file opened. If not, return \-1.

2a. If your ifstream object is called, e.g., `inputFile`, you can use `inputFile.is_open()` to get a bool that will be true if the file is open and false if not

3\. Create a counter variable, set it to 0\.

4\. Use a while loop: while (counter \< maxWords && inputFile \>\> words\[counter\])

5\. Inside the loop, just increment the counter.

6\. After the loop, close the file.

7\. Return the counter.

**Function 3: buildMarkovChain**

int buildMarkovChain(const std::string words\[\], int numWords, int order,

                     std::string prefixes\[\], std::string suffixes\[\],

                     int maxChainSize);

**What it does:** This function scans through all the words and records "what comes after what." It's like making flashcards: on the front of each card you write a word (or words), and on the back you write the word that came after it.

**Parameters explained:**

**words\[\]** – The array filled by readWordsFromFile (Function 2).

numWords – How many words are in that array.

order – How many words to use as the prefix. Order 1 means one word, order 2 means two words joined together.

prefixes\[\] – An empty array where you'll store the "front of the flashcard" (the word or words before).

suffixes\[\] – An empty array where you'll store the "back of the flashcard" (the word that came after).

maxChainSize – Maximum number of entries the arrays can hold.

**Returns:** The number of prefix-suffix pairs you added.

**Important:** You WILL have duplicates, and that's good\! If "the" is followed by "cat" twice and "dog" once, you'll have three entries. This is how we track probability.

**How to implement it:**

1\. Return 0 immediately if order is outside 1–3, numWords \<= order, or maxChainSize \<= 0\. Otherwise set count to 0\.

2\. Loop while i \< numWords \- order AND count \< maxChainSize, starting with i \= 0\. Each entry needs

   'order' words for the prefix PLUS one more word for the suffix.

3\. Inside the loop:

   \- Create the prefix by calling joinWords(words, i, order)

   \- The suffix is simply words\[i \+ order\]

   \- Store: prefixes\[count\] \= prefix;  suffixes\[count\] \= suffix;

   \- Increment count

   \- The loop condition checks capacity before the next array write.

4\. Return count.

**Example with order \= 1:**

If words \= \["the", "cat", "sat"\], then:

  i=0: prefix \= "the",  suffix \= "cat"

  i=1: prefix \= "cat",  suffix \= "sat"

**Example with order \= 2:**

If words \= \["the", "cat", "sat", "down"\], then:

  i=0: prefix \= "the cat",  suffix \= "sat"

  i=1: prefix \= "cat sat",  suffix \= "down"

**Function 4: getRandomSuffix**

std::string getRandomSuffix(const std::string prefixes\[\], const std::string suffixes\[\],

                            int chainSize, std::string currentPrefix);

**What it does:** Given a prefix like "the cat", this function finds ALL the entries in the chain that have that prefix, then randomly picks one of the corresponding suffixes. It's like flipping through your flashcards, finding all the ones with "the cat" on the front, and randomly picking one to see what's on the back.

**Parameters explained:**

prefixes\[\] – The array of prefixes from buildMarkovChain.

suffixes\[\] – The array of suffixes from buildMarkovChain.

chainSize – How many entries are in the chain.

currentPrefix – The prefix to look up (like "the" or "the cat").

**Returns:** A randomly chosen recorded suffix. If chainSize \<= 0 or the prefix has no matches, return an empty string "". Never compute rand() % 0\.

**How to implement it:**

1\. First, count how many times currentPrefix appears in the prefixes array.

   Loop through prefixes\[0\] to prefixes\[chainSize-1\].

   If prefixes\[i\] \== currentPrefix, increment a matchCount.

2\. If matchCount is 0, return "" (empty string \- prefix not found).

3\. In main.cpp:

3a. Include \<cstdlib\> and \<ctime\>.

3b. Call srand(time(0)) once at the start of main().

3c. Seeding once lets the sequence vary between runs. Runs started with the same time-based seed can repeat; repeated random choices are also valid.

4\. Pick a random number: int pick \= rand() % matchCount;

   This gives you a number from 0 to matchCount-1.

5\. Loop through the prefixes array again. Keep a counter for matches.

   When you find the 'pick'-th match, return the corresponding suffix.

6\. If somehow nothing was found, return "".

**Example:**

If prefixes \= \["the", "cat", "the", "the"\] and suffixes \= \["cat", "sat", "dog", "bird"\]

And we call getRandomSuffix with currentPrefix \= "the":

  \- We find "the" at positions 0, 2, 3 → matchCount \= 3

  \- pick \= rand() % 3 might give us 0, 1, or 2

  \- We return suffixes\[0\], suffixes\[2\], or suffixes\[3\] → "cat", "dog", or "bird"

**Function 5: getRandomPrefix**

std::string getRandomPrefix(const std::string prefixes\[\], int chainSize);

**What it does:** This function just picks a random prefix from your chain to use as the starting point for text generation. It's like closing your eyes and pointing at a random flashcard to start with.

**Parameters explained:**

prefixes\[\] – The array of prefixes.

chainSize – How many entries are in the chain.

**Returns:** A randomly selected prefix string, or an empty string "" when chainSize \<= 0\.

**How to implement it:**

1\. If chainSize \<= 0, return "". Otherwise generate an index: int index \= rand() % chainSize;

2\. Return prefixes\[index\];

Check for an empty chain before taking a remainder or indexing the array.

**Function 6: generateText**

std::string generateText(const std::string prefixes\[\], const std::string suffixes\[\],

                         int chainSize, int order, int numWords);

**What it does:** This is the fun one\! It "walks" the Markov chain to generate new text. It picks a random starting point, then keeps asking "what word comes next?" over and over, building up a sentence word by word.

**Parameters explained:**

prefixes\[\] – The array of prefixes.

suffixes\[\] – The array of suffixes.

chainSize – How many entries are in the chain.

order – The chain order (1, 2, or 3). You need this to know how to update the prefix.

**numWords** – The maximum number of output words, including the initial prefix. The user must request at least order words.

**Returns:** Up to numWords words. Stop early at a dead end; do not invent a transition or restart elsewhere to fill the quota. For an empty chain, invalid order, or numWords \< order, return "".

**How to implement it:**

1\. Return "" for chainSize \<= 0, order outside 1–3, or numWords \< order. Otherwise get a starting prefix with getRandomPrefix and store it in currentPrefix.

2\. Start your result string with this prefix.

3\. Split the prefix into a currentWords array with capacity 3; use only the first order elements:

  string currentWords\[3\]; // supports the validated orders 1, 2, and 3

  int wordIndex \= 0;                                                                                                                                                                 

  string temp \= "";

  for (int i \= 0; i \< currentPrefix.length(); i++) {                                                                                                                                 

      if (currentPrefix\[i\] \== ' ') {                                                                                                                                                 

          currentWords\[wordIndex\] \= temp;                                                                                                                                            

          wordIndex++;                                                                                                                                                               

          temp \= "";                 

      } else {                                                                                                                                                                       

          temp \+= currentPrefix\[i\];  

      }

  }

  currentWords\[wordIndex\] \= temp; // don't forget the last word

4\. Loop (numWords \- order) times:

  a. Call getRandomSuffix with currentPrefix and assign to a variable called newWord;                                                                                                                                        

  b. If it returns "", break (dead end).                                                                                                                                             

  c. Add a space and the new word to your result string.                                                                                                                             

  d. Update the sliding window:                                                                                                                                                      

    \- Loop from j \= 0 to j \< order \- 1: set currentWords\[j\] \= currentWords\[j \+ 1\]                                                                                                    

    \- After the loop, set currentWords\[order \- 1\] \= newWord                                                                                                                                          

    \- Rebuild: currentPrefix \= joinWords(currentWords, 0, order)                                                                                                                     

5\. Return the result string.

**Example walkthrough (order 1):**

Starting prefix: "The"

result \= "The"

Loop iteration 1: getRandomSuffix("The") returns "cat"

  result \= "The cat", currentPrefix \= "cat"

Loop iteration 2: getRandomSuffix("cat") returns "sat"

  result \= "The cat sat", currentPrefix \= "sat"

...and so on until the requested maximum is reached or no successor exists. The starting prefix counts toward the output limit.

**Git Commands Reference**

You are required to use git to track your progress. Here are the essential commands you'll need:

**Setting Up (only if not using Codespaces)**

*If you're using Codespaces, your repository is already set up – skip this section.* If you're working locally, you'll need one of these commands to get started:

git init

Creates a new git repository in your current folder.

git clone \<repository-url\>

Downloads an existing repository from GitHub to your computer.

**Checking Status**

git status

Shows which files have been modified, which are staged for commit, and which are untracked. Run this often to see what's going on\!

**Staging Files**

git add \<filename\>

Stages a specific file to be included in the next commit.

git add .

Stages ALL modified and new files. Use with caution – make sure you're not adding files you don't want\!

**Committing Changes**

git commit \-m "Your commit message here"

Saves your staged changes with a descriptive message. Write messages that describe WHAT you did, like "Implemented file reading function" or "Fixed bug in text generation".

**Pushing to GitHub**

git push

Uploads your commits to GitHub (or another remote repository). Your code isn't backed up until you push\!

If this is your first push to a new repository, you may need:

git push \-u origin main

**Typical Workflow**

After completing a piece of work:

git status                              \# See what changed

git add main.cpp markov.cpp markov.h    \# Stage the files

git commit \-m "Implemented buildMarkovChain"

git push                                \# Upload to GitHub

**Step-by-Step Implementation Guide**

Follow these steps in order. The detailed instructions for each function are in the "Required Functions" section above – refer back to them as you implement\! Complete and test each step before moving on. Make a git commit after each step.

**Step 1: Set Up Your Files**

Create your three files:

**markov.h** – Add include guards, \#include \<string\>, and all six function declarations from above.

**markov.cpp** – Include "markov.h" first, then the library headers this file uses (\<fstream\> and \<cstdlib\>). Start with function bodies returning 0 or "" as appropriate.

**main.cpp** – Include "markov.h", \<iostream\>, \<cstdlib\>, and \<ctime\>. Start with a main() that prints "Hello".

**Test:** 

g++ \-std=c++11 \-Wall \-Wextra \-pedantic main.cpp markov.cpp \-o markov

./markov

If it prints "Hello" with no errors, you're ready\!

*✓ Git commit. Run these commands:*

git status

git add .

git commit \-m "Set up project file structure"

git push

**Step 2: Implement joinWords**

Start with this easy helper function. Follow the implementation guide in Function 1 above.

**Test:** 

In main(), create a small array of words and call joinWords with different parameters:

std::string testWords\[\] \= {"the", "cat", "sat", "down"};

std::cout \<\< joinWords(testWords, 0, 2\) \<\< std::endl;  // Should print: the cat

std::cout \<\< joinWords(testWords, 1, 3\) \<\< std::endl;  // Should print: cat sat down

*✓ Git commit: "Implemented joinWords"*

**Step 3: Implement readWordsFromFile**

Follow the implementation guide in Function 2 above.

NOTE: If your ifstream object is called inputFile, you can use inputFile.is\_open() to get a bool that will be true if the file is open and false if not

**Test:** 

Create a small test file (like "test.txt") with a few sentences. Then in main():

std::string words\[1000\];

int count \= readWordsFromFile("test.txt", words, 1000);

std::cout \<\< "Read " \<\< count \<\< " words" \<\< std::endl;

for (int i \= 0; i \< 10 && i \< count; i++) {

    std::cout \<\< words\[i\] \<\< std::endl;

}

*✓ Git commit: "Implemented readWordsFromFile"*

**Step 4: Implement buildMarkovChain**

This is the trickiest function. Follow the implementation guide in Function 3 above carefully\!

**Test:** 

Build a chain and print the first 20 pairs to see if they look right:

std::string prefixes\[1000\], suffixes\[1000\];

int chainSize \= buildMarkovChain(words, count, 1, prefixes, suffixes, 1000);

for (int i \= 0; i \< 20 && i \< chainSize; i++) {

    std::cout \<\< "\[" \<\< prefixes\[i\] \<\< "\] \-\> \[" \<\< suffixes\[i\] \<\< "\]" \<\< std::endl;

}

Try with order 1 first, then test with order 2\. The prefixes should be two words joined with a space.

*✓ Git commit: "Implemented buildMarkovChain"*

**Step 5: Implement getRandomSuffix**

Follow the implementation guide in Function 4 above.

**Test:** 

Pick a prefix you saw in your chain printout. Call getRandomSuffix 10 times:

for (int i \= 0; i \< 10; i++) {

    std::cout \<\< getRandomSuffix(prefixes, suffixes, chainSize, "the") \<\< std::endl;

}

Every returned suffix must belong to the selected prefix. With two "cat" entries and one "dog" entry, each selection has a 2/3 chance of "cat". Ten draws may not show that ratio; repetition alone is not a bug.

*✓ Git commit: "Implemented getRandomSuffix"*

**Step 6: Implement getRandomPrefix**

Implement the empty-chain guard and random selection described in Function 5\.

**Test:** 

for (int i \= 0; i \< 5; i++) {

    std::cout \<\< getRandomPrefix(prefixes, chainSize) \<\< std::endl;

}

Every returned value must be a stored prefix. Repeated prefixes are allowed. Also test chainSize \= 0; the result must be "".

*✓ Git commit: "Implemented getRandomPrefix"*

**Step 7: Implement generateText**

This is the fun one\! Follow the implementation guide in Function 6 above.

**Test:** 

std::string output \= generateText(prefixes, suffixes, chainSize, 1, 20);

std::cout \<\< output \<\< std::endl;

Run several times and check that every transition exists in the chain. Repeated outputs are allowed. Test a dead end and a request equal to order as well.

*✓ Git commit: "Implemented generateText"*

**Step 8: Complete main()**

Now put it all together\! Your main() should:

1\. Add srand(time(0)); at the very beginning (for randomness).

2\. Ask for the filename, order, and maximum number of words. Reject nonnumeric input, order outside 1–3, or a requested count smaller than order; explain the problem and let the user try again.

3\. Use a named capacity, for example const int MAX\_WORDS \= 5000; declare words, prefixes, and suffixes with that capacity. Pass the actual capacity to the functions. This project may train on only the first 5000 words of a larger file.

4\. Read the file. Explain a \-1 result as a file-open failure. If the count is \<= order, explain that at least order \+ 1 training words are needed. Do not try to generate from those inputs.

5\. Build the chain and confirm chainSize \> 0 before random selection. If the input array filled to capacity, tell the user that at most MAX\_WORDS input words were used and additional words, if any, were ignored.

6\. Generate up to the requested number of words, stopping if a prefix has no successor.

7\. Print the generated text and its actual word count. If it is shorter than requested, explain that generation stopped at a dead end. Count the words in the returned text; do not change the required function signature.

*✓ Git commit: "Completed main program"*

**Step 9: Test and Polish**

1\. Test with different files. Try downloading a book from Project Gutenberg (gutenberg.org)\!

2\. Test with orders 1, 2, and 3\. Notice how the output changes.

3\. Test missing and empty files, whitespace-only input, fewer than order \+ 1 training words, invalid order/count input, an input exceeding capacity, and a terminal prefix. None should cause out-of-bounds access or a remainder by zero.

*✓ Git commit: "Final polish"*

**Tips and Hints**

**Array sizes:** Three local std::string arrays of 100000 elements can exhaust the stack before useful work begins. Use the modest 5000-word capacity above, check every bound, and explain the training limit. Storing a whole book is not required for this project.

**Random numbers:** Include \<cstdlib\> in each .cpp file that uses rand or srand, and \<ctime\> where time is used. Seed once at the start of main(). Use rand() % n only after confirming n \> 0; it is adequate for this introductory exercise, not a promise of different output every time.

**String comparison:** You can compare strings directly with \==. For example: if (prefixes\[i\] \== currentPrefix)

**Updating the prefix:** For order 2+, the trickiest part is updating the prefix. One approach: keep an array of the last N words (where N \= order), and use joinWords to rebuild the prefix string after each step.

**Sample Program Output**

Enter input filename: test.txt

Enter order (1, 2, or 3): 1

Enter maximum number of words to generate: 10

One possible run using the cat-story training text above:

`The cat saw the dog. The cat sat down.`  
`Generated 9 of at most 10 words. Stopped early: no successor for "down.".`

**Requirements Checklist**

☐ Project uses three files: main.cpp, markov.h, markov.cpp

☐ Header file has include guards and includes \<string\> itself

☐ All six required functions are implemented

☐ Program compiles with g++ \-std=c++11 \-Wall \-Wextra \-pedantic main.cpp markov.cpp \-o markov

☐ Program reads a user-specified text file up to its documented array capacity and reports file-open or insufficient-input errors

☐ Program supports order 1, 2, and 3

☐ Program generates at most the requested count, including the initial prefix; a dead end ends generation early with an explanation

☐ Random choices select valid stored entries; duplicates retain their weight and repeated output is allowed

☐ Git repository has multiple meaningful commits

**How to Submit**

When you have completed the project:

1\. Make sure all your changes have been committed and pushed to GitHub.

2\. Go to your repository on GitHub.

3\. Copy the URL from your browser's address bar. It should look something like:

https://github.com/yourusername/your-repo-name

4\. Go to Canvas and find this assignment.

5\. Paste the link to your repository and submit.

**Important:** Make sure I can access the repository. A public repository is one option; a private repository is fine if you have granted me access. Do not publish credentials or other private files.