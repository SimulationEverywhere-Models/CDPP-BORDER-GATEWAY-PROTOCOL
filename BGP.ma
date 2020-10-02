[top]
components : inputBuffer@inputBuffer BGPProcessor@BGPProcessor
out : Out 
in : In 

Link : In In1@inputBuffer
Link : Out1@inputBuffer ProcessorIn1@BGPProcessor
Link : ProcessorOut1@BGPProcessor Out
Link : ProcessorOut2@BGPProcessor reqIn@inputBuffer