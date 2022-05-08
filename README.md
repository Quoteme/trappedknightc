# Trapped Knight C

![trapped knight thumbnail](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fi.ytimg.com%2Fvi%2FRGQe8waGJ4w%2Fmaxresdefault.jpg&f=1&nofb=1)

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
