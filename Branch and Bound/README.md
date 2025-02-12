# Branch And Bound
Implementation of a Branch and Bound algorithm to select an appropriately representative cast of actors, in Python.
General idea:

𝐵𝑟𝑎𝑛𝑐ℎ_𝑎𝑛𝑑_𝑏𝑜𝑢𝑛𝑑(𝑘, 𝑖, 𝑋)
  if 𝑘 == 𝑝 and X is representative
  
    if 𝑐𝑜st(𝑋) < 𝑜𝑝𝑡
    
      𝑜𝑝𝑡 ← 𝑐o𝑠𝑡(𝑋)
      
      𝑥_𝑜𝑝𝑡 ← 𝑋
      
  else
  
    for 𝑗 from 𝑖 + 1 to 𝑛
    
      if 𝑋 is feasible and 𝑋 is optimal
      
        𝑋[𝑗 + 𝑘] ← 𝑗
        
        𝑘 ++
        
        𝐵𝑟𝑎𝑛𝑐ℎ_𝑎𝑛𝑑_𝑏𝑜𝑢𝑛𝑑(𝑘, 𝑗, 𝑋)
        
        𝑘 −−
        
