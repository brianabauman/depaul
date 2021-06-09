import scala.collection.mutable.Buffer

import akka.actor.{Actor, ActorSystem, ActorRef, Props}
import akka.event.Logging

sealed trait LoadMasterAPI
case class Start(maxPerNode: Int) extends LoadMasterAPI
case class BurstAck(senderNodeID: Int, stats: Stats, broadcastsReceived: Buffer[Int], broadcastsSent: Buffer[Int]) extends LoadMasterAPI
case class Join() extends LoadMasterAPI

/** LoadMaster is a singleton actor that generates load for the app service tier, accepts acks from
  * the app tier for each command burst, and terminates the experiment when done.  It uses the incoming
  * acks to self-clock the flow of commands, to avoid swamping the mailbox queues in the app tier.
  * It also keeps running totals of various Stats returned by the app servers with each burst ack.
  * A listener may register via Join() to receive a message when the experiment is done.
  *
  * @param numNodes How many actors/servers in the app tier
  * @param servers ActorRefs for the actors/servers in the app tier
  * @param burstSize How many commands per burst
  */

class LoadMaster (val numNodes: Int, val servers: Seq[ActorRef], val burstSize: Int) extends Actor {
  val log = Logging(context.system, this)
  var active: Boolean = true
  var listener: Option[ActorRef] = None
  var nodesActive = numNodes
  var maxPerNode: Int = 0
  var allBroadcastsSent: Buffer[Buffer[Int]] = Buffer.fill(numNodes){ Buffer.fill(numNodes){ 0 } }
  var allBroadcastsReceived: Buffer[Buffer[Int]] = Buffer.fill(numNodes){ Buffer.fill(numNodes){ 0 } }
  val serverStats = for (s <- servers) yield new Stats

  def receive = {
    case Start(totalPerNode) =>
      Thread.sleep(1000) //allow servers to prime

      maxPerNode = totalPerNode
      log.info("Master starting bursts")
      for (s <- servers)  burst(s)

    case BurstAck(senderNodeID: Int, stats: Stats, broadcastsReceived: Buffer[Int], broadcastsSent: Buffer[Int]) =>
      serverStats(senderNodeID) += stats
      updateBroadcastCounts(senderNodeID, broadcastsReceived, broadcastsSent)

      if (serverStats(senderNodeID).messages == maxPerNode) {
        nodesActive -= 1
        if (nodesActive == 0) deactivate()
      } else if (active) {
        burst(servers(senderNodeID))
      }

    case Join() =>
      listener = Some(sender)
  }

  def burst(server: ActorRef): Unit = {
    //log.info(s"send a burst to node $target")
    for (i <- 1 to burstSize)
      server ! Command()
  }

  def deactivate() = {
    Thread.sleep(1000) //allow final messages to arrive
    active = false

    //final output
    val total = new Stats
    serverStats.foreach(total += _)

    for (i <- 0 to numNodes - 1) {
      println(s"GroupServer$i stats: ${serverStats(i)}")
      for (j <- 0 to numNodes - 1)
        if (i != j)
          println(s"GroupServer${i} was sent ${allBroadcastsSent(j)(i)} messages from GroupServer${j} but received ${allBroadcastsReceived(i)(j)}...  ")
      println()
    }

    println(s"Total stats: $total")

    if (listener.isDefined)
      listener.get ! total
  }

  def updateBroadcastCounts(nodeID: Int, broadcastsReceived: Buffer[Int], broadcastsSent: Buffer[Int]) = {
    for (i <- 0 to numNodes - 1) {
      allBroadcastsReceived(nodeID)(i) += broadcastsReceived(i)
      allBroadcastsSent(nodeID)(i) += broadcastsSent(i)
    }
  }
}

object LoadMaster {
   def props(numNodes: Int, servers: Seq[ActorRef], burstSize: Int): Props = {
      Props(classOf[LoadMaster], numNodes, servers, burstSize)
   }
}

