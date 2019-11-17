Kyle Jeffrey
Partner: Aidan 
Submission: Use Aidan's Submission
Kyle: 
	-Message.c
	-Agent_Test_Harness.c
	-Field_Test_Harness.c
	-Negotiation_Test_Harness.c

Aidan:
	-Field.c
	-Agent.c
	-Negotiation.c
	-Message_Test_Harness.c 

Extra Credit:
	-Did smarter AI
	-

•A lab report, containing:

BattleBoats Overview:
Battleboats, based off the Hasbro game Battleship, used two pic32 microprocessors to simulate a game environment. Both Pic32's ran the same code and communicated with each other through their UART ports. The development of the game add three major parts as I see it. The front end graphical interface, the back end logic and data management of game data, and the messaging protocol structure the two systems used to communicate with each other. The front end was mostly given. It was only necessary to call the FieldOledDraw() function that was given, at the right places. The back end logic had everything to do with storing the player's boats on the field, tracking boat lives, tracking the appearance of the field, and tracking the appearance of the opponents field. Field.c and Agent.c primarily ran this. Lastly, the messaging system. This was handled by Message.c and Negotiation.c. The messaging protocol was how the two Pic32's sent their guess shot's and guess results. 

Q: What worked well?  
A: Having spent a lot of time on Message.c, I found that later on, I had no issues with the code and could trust that that any bug did not have to do with the messaging system.
 
Q: What didn’t?  
A: What didn't work is the converse of what I answered to the prior question. On Field.c and Agent.c, I did not test as extensively as I should've. This created major issues when finally connecting the Pic32's together and running the provided Lab_main file. One major issue was keeping track of lives. The Field.c function that kept track of lives did not have proper functionality, and this wasn't straightforward when the Pic32's would automatically fight. They would freeze up and get stuck in states.

Q: Describe at least one testing strategy you found effective.
A: I found that testing each other's code was actually very effective. I emphasized not looking at my partners code for the file I was testing. Sort of like a double blind placebo study, I didn't want the source code to affect my test harness. 
 
Q: What did you learn from this lab?
A: I learned a bit on using Git for version control. I learned group communication for projects. I think most importantly, I learned how to follow through with a large project from start to finish.

Q: What did you like about this lab?
A: I enjoyed having a partner. This is how almost all work environments are, and I found it forced me to have a better grasp of the assignment in order to communicate it with people.

Q: What would you change about this lab?
A: I have no complaints.