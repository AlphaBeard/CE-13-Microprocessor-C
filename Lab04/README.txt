Kyle Jeffrey

Summary of Lab 4: Creating a reverse polish notation calculator gave a concrete example of using a stack. This lab also increased the difficulty of slow and incrimental software development. Each new source file required other programmed files to work properly.

Difficulties with the Lab: The stack appeared to flow pretty fluidly for me and I didn't hit any roadblocks until the rpn_evaluate function. Working with pointers started to become especiallly difficult and I had to take moments to stop and completely restart on the function. Originally, I used strtok() for parsing the passed rpn sentence in the rpn_evaluate function, but it became ever present that this would introduce far more bugs than was worth. The case became that cutting corners and trying to impliment anything other than a simple char by char parse introduced more errors than convienence. 

Conclusion: Eventually, the parsing fell into place and the calculator was working with ease, and the game became about finding all the bugs there could be. This by far took the longest, as there are so many ways the program could be bugged out and it's difficult to think of all the corner cases. 