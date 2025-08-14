# Fair Simulation
By Andrew Metzroth for CSPB 2270 Data Structures
Last updated 08.13.2025 

# Concept
My overarching goal was to simulate a pedestrian street fair and the patrons using the fair with a variety of shopping strategies. I wanted to see how various strategies perform in relation to each other, and if I have time to work on specific optimization strategies for either booths to sell all their wares, or for shoppers to optimize the results of their list. I also wanted to be able to scale the results. The results of this project will be useful both for a data science-style analysis as well as a video game application where I might use a variation of this simulation to build a game in the future.

## Data Structures Used 
The major data structure here is an unweighted graph representing the fair. I'm using the implementation I built for our graphs project along with some extension to support weighted edges and my other classes.

In addition, the Booth and Patron classes are objects that take advantage of the graph structure for traversal. Both classes track inventory, the Patron also tracks state, location, and history for output post-simulation.

## Algorithms Used
While I haven't used a formal algorithm structure, I have developed a few algorithms to simulate patron behavior with nods to standard approaches. I have intentionally made Patrons who wander the fair in a lazy manner, move randomly and take a greedy approach to buying as much inventory as possible each step, and patrons who use a "peek ahead" approach to see what options are available to them.

----

# Implementation Notes - How to use and where to look.
The program **Fair.exe** should run on compile using the **Makefile** in the **build** folder. executing the file will run a simulated fair with some console output and two output csvs: `booths.csv` and `patrons.csv`. These log the sales at a given booth and the path of a patron as they move through the fair respectively, so you can track activity and compare strategies and locations.

If you'd like to mess with parameters, take a look at **main.cpp**; it contains most of the constants at the top of the file; changing the int values of these constants will modify the size of the simulation and its parameters. Have fun, it has scaled pretty well in testing!

You can also build a different graph than the default one I've included. I built this graph with a significant number of edges, so it might be fun to try something with more fixed paths.

### Important Code
To understand the code, you'll want to spend the most time in the **Patron** and **Booth** classes, as well as **main.cpp**. 

In **Patron**, the `movePatron()` function sticks out to me as the heart of the program. This runs once per Patron per simulation tick, and executes their move and purchase strategies with helper functions `moveLazy()`, `moveGreedy()`, and `movePeek()` (the last is the most complicated).

In **Booth** and **Patron**, the `Patron::buyItem()` and `Booth::sellItem()` functions (and how they work in tandem) is important to understanding how a list is updated.

**main.cpp** actually runs the simulation and sets most of the parameters through constants (right now there are a few in **Patron** as well). This is the "have fun and tinker" section. Play with it if you want to try different runs!

### Minor changes
The Edge, Graph, and Node Header/source files are all very similar to our class project. I extended them in the following ways:
- Each node contains one Booth* pointer, so that it can hold a booth.
- Each edge contains a "weight" int, which is used in movement algorithms to deduct "steps" from a patron.

----

# Self-Evaluation
Boy did I learn a lot in this project! It was by far the most complex thing I've attempted in this class, even though in the end I only wrote about 500 lines of code plus some modifications of existing code. It was also interesting to essentially be designing my own movement algorithms (as well as a relatively encapsulated system for buying and selling an item). Making the Booth and Patron objects "talk" to one another was one of the real challenges here.

It was also interesting working on this project with less structure than we had had previously. I had to consciously think about every function I needed, and when to make changes to an existing class. I appreciated the freedom, and also loathed it as I was planning. Good opportunity to really think through some problems, though.

Overall I'm happy with where I ended up. Right now the code delivers all of the core functions I think it needs to: It runs a simulation successfully, shows off different strategies, and has a variety of parameters to choose from. I think this base is a great first step for extending, building more complex search-and-buy algorithms, and eventually allowing a "player" to interact with the simulation more directly. It's actually taught me a lot about how I might build something like this in a turn-based game environment, which was the other thing I wanted to learn.

## New Things
Things I learned during this project included:
- The pair datatype! I loved using this to solve a number of small problems with logging and containing data values in a map. It's an easy template to understand, but the applications for it are really cool.
- Plenty of learning about iterators this time! Part of this was my choice to house inventories and shopping lists in maps, as it meant I had to iterate overt them quite a bit. 
- I periodically took specific time to clean up my code, document with comments, and find ways to add clarity in this project. This was very useful when working over several days, because it made my code more readable when I returned to it. If something wasn't readable, making it readable helped me remind myself of what I was doing.
- Super fun to debug a giant series of loops that call other loops under certain conditions! While the debugger was somewhat useful for this process, my real success was in the classic "print a cout statement that says what part of the program you've reached and a variable" method. Using this helped me find a couple segmentation faults and misconceptions about my move loops.
- Building code that logs its activity was new to me! I enjoyed doing this and making somewhat readable output.
- Makefile is new to me and I got it to work. Yay!

## Choices
Some important choices I made, most of them related to limiting scope:
- Simplification was the word of the day! For now I eliminated exits, randomized graph generation and one or two of my proposed movement strategies in favor of getting the entire simulation up and running. That seems to have worked, as I have a working sim!
- Re-use of existing data structures. I had a false start before this second attempt where I tried to implement my weighted graph as an adjacency list so that I could learn a new methodology. After several hours of tinkering with that, I realized I was getting lost in the data structure and it would be better for the project if I re-used the graph foundation we had, extending it to create weighted graph support.
- Originally I had planned on using linked lists to create my history files, but since I was working with a series of text strings I found it more expedient in practice to use a vector of strings.
- Once I had the simulation debugged and working it was time to add final clarity and readability, file stream outputs, and any other bells and whistles that I could manage in the time I had. I'm glad I identified these as optional features instead of forcing them early!


----

# Future extensions
I have a great TODO list for this:
- Randomized or procedural graph construction with parametized rules.
- Add exits and pathfinding for patrons (such as Dijkstra's shortest path or A* pathing) to enter/exit the fair and find items.
- Allow for multiple booths at each node and empty nodes.
- Allow for multiple repeat items on a shopping list, possibly with a multimap or other struct.
- Split movePatron and shopPatron into two encapsulated functions for greater strategic flexibility.
- Allow patrons to bid on items that they need to complete their set.
- Better identification of failed state for patrons (right now there's some overly repetitive wandering).
- More and more complicated patron strategies.
- save output to csv.
- Optimization for more efficient runtimes and reporting at large scale.
