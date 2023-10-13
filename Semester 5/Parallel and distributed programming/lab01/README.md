    Summation with fixed structure of inputs
We have to keep the values of some integer variables. Some of them are primary variables; they represent input data. The others are secondary variables, and represent aggregations of some other variables. In our case, each secondary variable is a sum of some input variables. The inputs may be primary or secondary variables. However, we assume that the relations do not form cycles.
At runtime, we get notifications of value changes for the primary variable. Processing a notification must atomically update the primary variable, as well as any secondary variable depending, directly or indirectly, on it. The updating shall not re-compute the sums; instead, you must use the difference between the old value and the new value of the primary variable.
From time to time, as well as at the end, a consistency check shall be performed. It shall verify that all the secondary variables are indeed the sums of their inputs, as specified.
Two updates involving distinct variables must be able to proceed independently (without having to wait for the same mutex).


    Common requirements
1. The problems will require to execute a number of independent operations, that operate on shared data.
2. There shall be several threads launched at the beginning, and each thread shall execute a lot of operations. The operations to be executed are to be randomly choosen, and with randomly choosen parameters.
3. The main thread shall wait for all other threads to end and, then, it shall check that the invariants are obeyed.
4. The operations must be synchronized in order to operate correctly. Write, in a documentation, the rules (which mutex what invariants it protects).
5. You shall play with the number of threads and with the granularity of the locking, in order to asses the performance issues. Document what tests have you done, on what hardware platform, for what size of the data, and what was the time consumed.
