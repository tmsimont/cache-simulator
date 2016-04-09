## UML
I created this with a tool called [ArgoUML](http://argouml.tigris.org/). I've never used the tool before, it was easy to download and get started if you want to use this.

![diagram](https://raw.githubusercontent.com/tmsimont/cache-simulator/master/uml/ClassDiagram.png)

This is a refined outline of what we discussed Tuesday for the structure of the processing part of the simulator. I'm thinking this will be a good start for discussion on how we want to break up the code. I used actual UML syntax here...

If you're curious, there is a good write-up available here: [Understanding UML Class Relationships](https://vaughnvernon.co/?page_id=31). You don't have to get into this, but I thought it would help to be accurate.

### Details

#### CacheSimulator, CacheArchitecture 
I'm thinking our main driver will be CacheSimulator. This will read input parameters for the cache, and generate a CacheArchitecture instance.

* The CacheArchitecture instance will contain several Cache instances (L1, L2)
* Each Cache instance will have 1 to many CacheSet instances.
  * Each Cache instance may or may not also have WriteBuffer or VictimBuffer instances, which will contain evicted CacheBlocks.
* Each CacheSet instance will have many CacheBlock instances.
* The CacheBlocks contain bits for valid, tag and data.

##### TODO:

- [ ]  We need to figure out how the cache interacts with WriteBuffer and VictimBuffer. 
- [ ]  We also need to decide how the cache is initially populated. I'm thinking we might have a link to a MainMemory class, which we might expand to paging and page tables if we are ambitious.


#### CacheSearch
I'm thinking that CacheSimulator will read each line from the trace, and pass simulation of each line to a different InstructionSimulation instance -- depending on what kind of instruction we have.

The InstructionSimulation might be a ReadSimulation or a WriteSimulation. It will use an instance of CacheSearch to search a specfic Cache in the CacheArchitecture.

The InstructionSimulation instance will generate CacheEvent instances, based on what happens with CacheSearch, and return a list of CacheEvents to the CacheSimulator.

##### TODO:
- [ ]  Figure out how to use CacheSearch with Cache instance, and extract useful CacheEvent instances
- [ ]  Maybe get the GPU involved as an extension of the CacheSearch

#### CacheEvent
A new CacheEvent should be generated for any major event, such as a read miss, hit, write miss, use of victim buffer, etc.

The CacheSimulator will keep a list of events. Each event will have a specific time. We can then export the list in JSON or XML to a file that can be read by the animation layer.

