.section .data
  topoInicialHeap:  .quad 0
  inicio_heap:      .quad 0
  topo_heap:        .quad 0
  temp:             .quad 0
  temp2:            .quad 0
  i:                .quad 0
  bestFit:          .quad 0
  nextFit:          .quad 0
  num_bytes:		.quad 0
  bloco:			.quad 0
  extra:			.quad 0
  str1:             .string "\n"
  str2:             .string "################"
  str3:             .string "-"
  str4:             .string "+"
  str5:             .string "test %d\n"
  str6:				.string "\n"
  cabecalho:		.string "################"

.section .text
.globl iniciaAlocador
.globl finalizaAlocador
.globl meuAlocaMem
.globl meuLiberaMem
.globl imprMapa

iniciaAlocador:
  pushq %rbp
  movq %rsp, %rbp
  mov $str1, %rdi               #printf("inicializando alocador\n");
  call printf
#  mov $str5, %rdi
#  movq topoInicialHeap, %rsi
#  call printf
  movq $12, %rax                #topoInicialHeap = sbrk(0);
  movq $0, %rdi
  syscall
  movq %rax, topoInicialHeap
#  mov $str5, %rdi
#  movq topoInicialHeap, %rsi
#  call printf
  movq topoInicialHeap, %rbx    #inicio_heap = topoInicialHeap;
  movq %rbx, inicio_heap
  movq %rbx, topo_heap          #topo_heap = topoInicialHeap;
  movq %rbx, temp               #temp = inicio_heap;
#  mov $str5, %rdi
#  movq temp, %rsi
#  call printf
  popq %rbp
  ret

finalizaAlocador:
  pushq %rbp
  movq %rsp, %rbp
  movq $12, %rax
  movq topoInicialHeap, %rdi
  syscall
#  addq $16, %rax
#  movq %rax, %rdi
  popq %rbp
  ret

meuAlocaMem:
  pushq %rbp
  movq %rsp, %rbp
  movq %rdi, num_bytes		#%rbx contém long int num_bytes
  movq %rdi, %rbx
#  movq $str5, %rdi
#  movq %rbx, %rsi
#  call printf

  movq %rbx, %rdx           #int num_bytes
#  movq $str5, %rdi
#  movq %rdx, %rsi
#  call printf
  movq topo_heap, %rbx          #registradores para cmpq
  movq topoInicialHeap, %rcx
  cmpq %rcx, %rbx               #if (topo_heap == topoInicialHeap)
  jne else
    movq $12, %rax                #brk(num_bytes+inicio_heap+16);
    movq num_bytes, %rdi
    addq inicio_heap, %rdi
    addq $16, %rdi
    syscall
    movq num_bytes, %rdx
    addq %rdx, topo_heap          #topo_heap = num_bytes+topo_heap+16;
    addq $16, topo_heap
    movq inicio_heap, %rbx        #*(int *) inicio_heap = 1;
    movq $1, (%rbx)
  #  movq (%rbx), %rcx
  #  movq $1, (%rcx)
  	movq inicio_heap, %rbx
    addq $8, %rbx                 #*(int *) (inicio_heap + 8) = num_bytes;
    movq num_bytes, %rdx
    movq %rdx, (%rbx)
  #  movq (%rbx), %rcx
  #  movq %rdx, (%rcx)
    movq inicio_heap, %rax        #return inicio_heap + 16;
#    movq $str5, %rdi
#	movq topoInicialHeap, %rsi
#	call printf
    addq $16, %rax
    movq %rax, %rdi
    popq %rbp
    ret
  else:
  movq $0, i
  movq $0, %rdi
    movq inicio_heap, %rax        #temp = inicio_heap;        FIRST FIT
    movq %rax, temp
    movq $0, %rdi                 #i = 0
    movq $0, i
    #jmp while
    while:                        #while (i == 0)
    cmpq $0, %rdi
    jne fim_while
      movq temp, %rbx             #if (*(int *) temp == 0)
      movq (%rbx), %rcx
      cmpq $0, %rcx
      jne else1
      	movq temp, %rbx
        addq $8, %rbx               #if (*(int *) (temp + 8) >= num_bytes)
        movq (%rbx), %rcx
        movq num_bytes, %rdx
        cmpq %rdx, %rcx
        jl else2
          movq $1, %rdi               #i = 1;
          movq $1, i
          jmp if_fim

        else2:                      #else
          movq temp, %rbx           #temp = temp + *(int *) (temp + 8) + 16;
          addq $8, %rbx
          movq (%rbx), %rcx
          #subq $8, %rbx
          addq $16, %rcx
          movq temp, %rbx
          addq %rcx, %rbx
          #addq $16, %rbx
          movq %rbx, temp
          jmp if_fim

      else1:                      #else
        movq temp, %rbx           #temp = temp + *(int *) (temp + 8) + 16;
        addq $8, %rbx
        movq (%rbx), %rcx
        movq temp, %rbx
        addq %rcx, %rbx
        addq $16, %rbx
        movq %rbx, temp

      if_fim:
        movq temp, %rbx           #if (temp == topo_heap)
        movq topo_heap, %rcx
        cmpq %rcx, %rbx
        jne else3
        movq $1, i                #i = 1;
        movq $1, %rdi
      else3:
        jmp while

    fim_while:
      movq temp, %rbx             #if (temp > topo_heap)
      movq topo_heap, %rcx
      cmpq %rcx, %rbx
      jle else4
      	movq topo_heap, %rcx
        movq %rcx, temp             #temp = topo_heap;
        
    else4:
      movq temp, %rbx             #if (temp == topo_heap)
      movq topo_heap, %rcx
      cmpq %rcx, %rbx
      jne else5
        movq $12, %rax              #brk(num_bytes+temp+16);
        movq num_bytes, %rdi
        movq temp, %rbx
        addq %rbx, %rdi
        addq $16, %rdi
        syscall
        movq num_bytes, %rbx         #topo_heap = num_bytes+topo_heap+16;
        addq topo_heap, %rbx
        addq $16, %rbx
        movq %rbx, topo_heap
    else5:
      movq temp, %rbx             #*(int *) temp = 1;
      movq $1, (%rbx)
      
      movq temp, %rbx             #extra = *(int *) (temp + 8);
      addq $8, %rbx
      movq (%rbx), %rcx
      movq %rcx, extra
      
      movq temp, %rbx
      addq $8, %rbx               #*(int *) (temp + 8) = num_bytes;
      movq num_bytes, %rcx
      movq %rcx, (%rbx)
      movq topoInicialHeap, %rax  #inicio_heap = topoInicialHeap;
      movq %rax, inicio_heap
      movq temp, %rbx             #if (temp + 16 + num_bytes < topo_heap)
      addq $16, %rbx
      movq num_bytes, %rcx
      addq %rcx, %rbx
      movq topo_heap, %rdx
      cmpq %rdx, %rbx
      jge else6
        movq temp, %rbx             #*(int *) (temp + 16 + num_bytes) = 0;
        addq $16, %rbx
        movq num_bytes, %rcx
        addq %rcx, %rbx
        movq $0, (%rbx)
#        movq temp, %rbx             #*(int *) (temp + 16 + num_bytes + 8) = topo_heap - (temp+32+num_bytes);
#        addq $16, %rbx
#        movq num_bytes, %rcx
#        addq %rcx, %rbx
#        addq $8, %rbx
#        movq topo_heap, %rcx
#        movq temp, %rdx
#        movq num_bytes, %rax
#        subq %rdx, %rcx
#        subq $32, %rcx
#        subq %rax, %rcx			#alterado para
#        movq %rcx, (%rbx)		
								
		movq extra, %rbx			#*(int *) (temp + 16 + num_bytes + 8) = extra - num_bytes - 16;
		subq num_bytes, %rbx
		subq $16, %rbx
		movq temp, %rcx
		addq $24, %rcx
		addq num_bytes, %rcx
		movq %rbx, (%rcx)
		
		
		
		
    else6:
      movq temp, %rax             #return temp + 16;
      addq $16, %rax
      movq %rax, %rdi
      popq %rbp
      ret

meuLiberaMem:
	pushq %rbp
	movq %rsp, %rbp
	movq %rdi, bloco	            #void* bloco
  
	movq bloco, %rbx				#*(int *) (bloco - 16) = 0;
	subq $16, %rbx
	movq $0, (%rbx)
	movq $0, i
	movq $0, %rdi
	movq inicio_heap, %rcx			#temp = inicio_heap;
	movq %rcx, temp
	while10:
	movq temp, %rbx					#while (temp != topo_heap)
	movq topo_heap, %rcx
	cmpq %rcx, %rbx
	je fim_while10
		movq temp, %rbx				#if(*(int *) temp == 0)
		cmpq $0, (%rbx)
		jne else10
			movq temp, %rbx			#if (*(int *) (temp + *(int *) (temp+8) + 16) == 0)
			addq $8, %rbx
			movq (%rbx), %rcx
			addq $16, %rcx
			movq temp, %rbx
			addq %rbx, %rcx
			cmpq $0, (%rcx)
			jne else10
				movq temp, %rbx		#extra = *(int *) (temp + *(int *) (temp+8) + 24);
				addq $8, %rbx
				movq (%rbx), %rcx
				addq $24, %rcx
				movq temp, %rbx
				addq %rbx, %rcx
				movq (%rcx), %rbx
				movq %rbx, extra
				movq temp, %rbx		#extra += *(int *) (temp+8);
				addq $8, %rbx
				movq (%rbx), %rcx
				addq extra, %rcx
				movq %rcx, extra
				addq $16, extra		#extra += 16;
				movq temp, %rbx		#*(int *) (temp + 8) = extra; 
				addq $8, %rbx
				movq extra, %rcx
				movq %rcx, (%rbx)
				
		else10:
			movq temp, %rbx				#temp = temp + *(int *) (temp+8) + 16;
			addq $8, %rbx
			movq (%rbx), %rcx
			addq $16, %rcx
			movq temp, %rbx
			addq %rbx, %rcx
			movq %rcx, temp
	jmp while10
		
	fim_while10:
	
	movq inicio_heap, %rcx			#temp = inicio_heap;
	movq %rcx, temp
	while11:
	movq temp, %rbx					#while (temp != topo_heap)
	movq topo_heap, %rcx
	cmpq %rcx, %rbx
	je fim_while11
		movq temp, %rbx				#if(*(int *) temp == 0)
		cmpq $0, (%rbx)
		jne else11
			movq temp, %rbx			#if (*(int *) (temp + *(int *) (temp+8) + 16) == 0 && (temp + *(int *) (temp+8) + 16) != topo_heap)
			addq $8, %rbx
			movq (%rbx), %rcx
			addq $16, %rcx
			movq temp, %rbx
			addq %rbx, %rcx
			cmpq $0, (%rcx)
			jne else11
			movq temp, %rbx			#&&
			addq $8, %rbx
			movq (%rbx), %rcx
			addq $16, %rcx
			movq temp, %rbx
			addq %rbx, %rcx
			movq topo_heap, %rbx
			cmpq %rbx, %rcx
			je else11
			
			
			
				movq temp, %rbx		#extra = *(int *) (temp + *(int *) (temp+8) + 24);
				addq $8, %rbx
				movq (%rbx), %rcx
				addq $24, %rcx
				movq temp, %rbx
				addq %rbx, %rcx
				movq (%rcx), %rbx
				movq %rbx, extra
				movq temp, %rbx		#extra += *(int *) (temp+8);
				addq $8, %rbx
				movq (%rbx), %rcx
				addq extra, %rcx
				movq %rcx, extra
				addq $16, extra		#extra += 16;
				movq temp, %rbx		#*(int *) (temp + 8) = extra; 
				addq $8, %rbx
				movq extra, %rcx
				movq %rcx, (%rbx)
				
		else11:
			movq temp, %rbx				#temp = temp + *(int *) (temp+8) + 16;
			addq $8, %rbx
			movq (%rbx), %rcx
			addq $16, %rcx
			movq temp, %rbx
			addq %rbx, %rcx
			movq %rcx, temp
	jmp while11
		
	fim_while11:
		
  
	movq $0, %rax
	popq %rbp
	ret
	

imprMapa:
	pushq %rbp
	movq %rsp, %rbp
	movq inicio_heap, %rax
	movq %rax, temp
	while4:
		movq temp, %rax				#while (temp < topo_heap)
		movq topo_heap, %rbx
		cmpq %rbx, %rax
		jge fim_while4
			mov $str2, %rdi			#printf("################");
			call printf
			movq $0, i				#for (i = 0; i < *(int *) (temp + 8); i++)
			movq $0, %rdi
			
		for:
			movq temp, %rax
			addq $8, %rax
			movq (%rax), %rbx
			movq i, %rdi
			cmpq %rbx, %rdi
			jge fim_for
				movq temp, %rax		#if (*(int *) temp == 0)
				movq (%rax), %rcx
				cmpq $0, %rcx
				jne else9
				mov $str3, %rdi		#printf("-");
				call printf
				addq $1, %rdi
				addq $1, i
				jmp for
			else9:
				mov $str4, %rdi		#printf("+");
				call printf
				addq $1, %rdi
				addq $1, i
				jmp for
		fim_for:
			movq temp, %rax			#temp = temp + (*(int *) (temp + 8) + 16);
			movq temp, %rbx
			addq $8, %rbx
			movq (%rbx), %rcx
			
			addq $16, %rcx
			
			movq temp, %rax
			
			addq %rcx, %rax
			
			movq %rax, temp
			
			jmp while4
	fim_while4:
		mov $str1, %rdi			#printf("\n");
		call printf
	popq %rbp
	ret
	



















#_start:
