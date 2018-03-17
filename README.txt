Name:  Shehtab Zaman
BU Account: szaman5
BU ID: 00540096

I did the extra credit using perceptrons. I implemented
the perceptron using the method mentioned in [1]. Using
a 52 entry table and 9 bit global history I was able to beat
the tournament predictor.

I also extended the perceptron branch to include a concurrent
gshare and implemented a sort of perceptron with agree.
The implementation was similar to tournament and the resulting
accuracy was >99%.

The program for a long trace runs for about 3 minutes on the g7 computer.
Make:
Make - builds ./predictor
Make ec - builds driver with perceptron driver code

[1] Jimenez, Daniel, &, Lin Calvin. Neural Methods for Dynamic Branch Prediction.
