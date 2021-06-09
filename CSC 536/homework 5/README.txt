To run this program:
- Open the GroupService folder, build with sbt, and run
- Options can be configured in src/main/scala/TestHarness.scala, such as:
	- number of nodes
	- size of bursts
	- total messages sent to each node
- The default options are 10 nodes, bursts of 1000, and a total of 10000 messages per node.

Questions/insights:

- Do actors ever receive messages originating from a given actor out of order? What if the messages are forwarded through an intermediary?

I added logic to the program to attach a sequence number with each message that is broadcast to a group. This sequence number is unique to a particular GroupServer actor and increments with each broadcast (even if there are no other servers in the group). With this logic in place, the GroupServer actors are also able to record the last sequence they received from a given GroupServer, enabling them to confirm that each sequence they receive is newer than any they've seen before. In the case that a GroupServer receives a sequence number _older_ than one it has processed before, it will record a "misordered" statistic and continue processing. In practice, I did not observe any misordered messages.

Were there to be an intermediary actor responsible for passing along messages, I believe there would be an equally low probability of messages being misordered, as the messages from GroupServer1 --> Intermediary would remain ordered and the messages from Intermediary --> GroupServer2 would, as well. I did not implement this approach.

- What if two actors multicast to the same group? Does each member receive the messages in the same order?

This was the most difficult question for me to implement, as I struggled to design a quick, reliable method for answering this question. It relies on a few pieces of knowledge that are not readily available in my implementation, such as -- "What other servers were in a given group when both messages were multicast?", "What order did another server receive messages in and was it the same as mine?", "Which servers were supposed to receive each of the two messages, but didn't, and why?", etc.

I believe that there is no guarantee that all servers will receive the multicast messages in the same order, but have no way to demonstrably prove this. One possible approach would be to print, for every message sent and received, who the members of the destination group were, who sent the message, who received the message, etc., using Lamport timestamps or vector clocks to organize the printed statments quasi-linearly. You could then attempt to tell a story that answers this question more thoroughly.

- Do actors ever receive messages for groups "late", after having left the group?

My implementation was able to answer this questions by including the destination group ID in the body of each broadcast message and asking "Am I still in the listed group?" upon receipt of any broadcast message. When you are no longer in a group, but receive a broadcast message destined for that group, you record a "late" statistic. The output of the program demonstrates that this phenomenon happens quite frequently, which is to be expected -- there is no guarantee that a recipient will remain in the group any longer than the moment you query group membership when crafting the broadcast message. I don't see this as too big a problem... servers that receive messages for groups they are no longer a part of can simply ignore them.

- How does your choice of weights and parameters affect the amount of message traffic?

There seem to be two factors at play. One is the difference in the join and leave percentage. The larger this gap (in favor of leave), the number of sent messages rapidly decreases as the average server is a member of fewer and fewer groups. The other is the broadcast percentage itself, which seems to have a more linear correlation with the number of messages sent.

My model is able to produce results for any combination of these three levers as long as their sum doesn't exceed 100%.

- How can you be sure your code is working, i.e., the right actors are receiving the right messages?

This one was tough for me, but I extended my stats tracking to record, for each server, the number of messages sent to and received from each other individual server. Then, by aggregating this data in the LoadMaster, we can compare the total of messages that server A thinks it sent to server B with the total number of messages that Server B actually received.

The results are not surprising -- many messages are not received, but some servers receive all messages. I'm not fully sure of why they didn't receive them, but it likely has to do with load on the system -- smaller tests had less drastic differences in sent/received.