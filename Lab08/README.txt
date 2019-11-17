Kyle Jeffrey

Summary: 
This lab introduced recursion, a complicated topic to follow at times. Using an implementation of a binary tree, letters of the morse alphabet were stored in a six layer binary tree. Using a button on our pic32 IO shield, a dot and dashes were inputted based on time constraints run by a state machine. The program would then decode the input and decrypt into alphabetical characters including spaces.

Approach: 
The iterative design process began with implimenting the binary tree library. The code was aesthetically very simple but logically difficult to wrap my head around. After testing the library, I moved onto the morse library, in charge of throwing morse event flags and decoding these flags into characters. I used state machines for both morseCheckEvents() and MorseDecode(). 

Conclusion: 
In total, the lab probably took me 15 or so hours. I had considerable more issue with this lab vs previous ones. Extra conceptual work had to be done to understand the recursion part of the lab, and the rest of the lab just took considerable debug time accounting for edge cases. 