
Descripition:
The problem is originally a problem about simulation of a concurrent eating schedule among multiple actors, and part of a project task of 42 coding school ciriculum. In this problem, the core is to solve the corordination of multiple dining philosophers, or I rather call them the eaters, under given specific rules. 

Mandotory part: 
In the mandatory part, the threads is required to simlulate eaters life cycles, which pulls out the needs of using mutex to avoid race windows of reaching the shared resources, which in this problem is grabbing the forks for eating.
(replace this with terms: ) As part of the rule, to acquire the shared fork, eater must wait in a non-deterministic manner for the fork to be released from other eaters. (A precondition: eater needs both forks in their left and right side to start eating.)  And eater would only willing to put down forks after they have done eating. This requires a specifically designed algorithm to coordinate the conflicts of acquiring the forks or it would cause a deadlock, per say none could eat without enough forks. 

To use this program, 
simply do : 
And to check the memory leak, use:
To check the states of threads, do:. 




