## Trace

This folder will contain all of the files necessary for working with the actual simulation side, which is going to be C++ source files?


### Major classes

* Trace generation
* Trace parsing
* Trace simulation
    * read parameters
    * apply metrics for trace events
    * record trace events on a timeline


### Timeline events for animation

* New instruction
* Search L1
* Find in L1
* Miss in L1
* Write in L1
* Execute write policy from L1 -> L2
* Cache coherence?
* Search L2
* Find in L2
* Miss in L2
* Write in L2
* Execute write policy from L2 -> main memory
* Update victim buffer (include source of data)
* Update write buffer (include source of data)

### Timeline data
* Event
* Parameters for event
* Time at which event occured
* Time since last event


