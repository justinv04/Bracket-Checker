# Assignment 3: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Justin Vincent

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers
1. How long did the program take with each version (You will need more than the test data)?  Describe what differences in run time you expect for your implementation. What you see in your experiments?

   > I tested my files on a copy of DSVector_bad.h which I copy and pasted until it was 5600 times longer than the original. DSStackArray ran much better than DSStackList, taking an average of ~600ms to run compared to an average of ~700ms

2. Discuss the difference in memory usage based on your implementation. You will need to think about how the versions store data.

   > the DSStackArray stores brackets in an array, so the memory usage is constant and determined by the size of the Stack's array. DSStackList uses a singly linked list to store data with pointers, so it uses dynamic memory.  

3. Which version would you use in practice. Why?

   > Despite using more memory than necessary at times, DSStackArray doesn't ever use that much, where as DSStackList would take significantly longer for not much benefit to memory usage. DSStack is the better option for most use cases.

4. Make sure that your stack implementation does not have memory leaks.

   ```
   From DSStackArray:
   ==13326== HEAP SUMMARY:
   ==13326==     in use at exit: 0 bytes in 0 blocks
   ==13326==   total heap usage: 2,511 allocs, 2,511 frees, 448,734 bytes allocated
   ==13326== 
   ==13326== All heap blocks were freed -- no leaks are possible
   ==13326== 
   ==13326== For lists of detected and suppressed errors, rerun with: -s
   ==13326== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
   From DSStackList:
   ==21609== HEAP SUMMARY:
   ==21609==     in use at exit: 0 bytes in 0 blocks
   ==21609==   total heap usage: 2,583 allocs, 2,583 frees, 471,993 bytes allocated
   ==21609== 
   ==21609== All heap blocks were freed -- no leaks are possible
   ==21609== 
   ==21609== For lists of detected and suppressed errors, rerun with: -s
   ==21609== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
   ```

5. Did you attempt any bonuses? If so, please give a brief description of what you did.

   > Yes, I made sure that my code removed commets using // from the line, while keeping any code that came before it. This does not include multi-line comment functionality cause that would be really hard given my current code structure and I didn't want to.
