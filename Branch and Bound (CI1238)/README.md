# Branch And Bound
Implementation of a Branch and Bound algorithm for selecting an appropriately representative cast of actors, in Python.

Given a set of S groups, a set of A actors, a set of P characters, and for each actor 𝑎 ∈ 𝐴 a set 𝑆𝑎 ⊆ 𝑆 of all groups the actor belongs to, the algorithm must find a cast in which every character has an actor, and all groups have a representative. Each actor also has an associated cost, 𝑣𝑎, and the total cost of the cast must be minimal. 
