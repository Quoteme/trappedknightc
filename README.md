# Trapped Knight C

![trapped knight thumbnail](https://i.ytimg.com/an_webp/RGQe8waGJ4w/mqdefault_6s.webp?du=3000&sqp=COSr3pMG&rs=AOn4CLCEtcY9-MrDLbaK7HKv5ZHF2on8Kg)

This is [trapped knight](https://www.youtube.com/watch?v=RGQe8waGJ4w&t=133s)
written in C. In ```./src/trappedknight.c``` you
can change how each knight will step, how many knights should be run,
what their maximum number of steps is before terminating, how many
threads should be run simultaneously, etc.

This greatly improves performance. The simple knight with step (1,2)
and starting position (0,0) will for example take less than half a millisecond
on my old Thinkpad X201T to calculate all 2016 steps before terminating.

Thanks to Stefan Schulz for recommending this problem to me.

Also see my previous work on this problem using Haskell:
[Quoteme/TrappedKnight](https://github.com/quoteme/trappedknight)
