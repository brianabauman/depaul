import scala.collection.mutable.Buffer

import akka.actor.{Actor, ActorSystem, ActorRef, Props}
import akka.event.Logging

case class Broadcast(groupID: BigInt, senderSequence: Int)

/**
 * GenericService is an example app service for the actor-based KVStore/KVClient.
 * This one stores Generic Cell objects in the KVStore.  Each app server allocates new
 * GenericCells (allocCell), writes them, and reads them randomly with consistency
 * checking (touchCell).  The allocCell and touchCell commands use direct reads
 * and writes to bypass the client cache.  Keeps a running set of Stats for each burst.
 *
 * @param myNodeID sequence number of this actor/server in the app tier
 * @param numNodes total number of servers in the app tier
 * @param storeServers the ActorRefs of the group servers
 * @param burstSize number of commands per burst
 */

class GroupServer (val myNodeID: Int, val numNodes: Int, storeServers: Seq[ActorRef], burstSize: Int) extends Actor {
  val generator = new scala.util.Random
  val cellstore = new KVClient(storeServers)
  val log = Logging(context.system, this)

  var stats = new Stats
  var nodeID = myNodeID
  var myGroups: Seq[BigInt] = Seq(myNodeID)
  var otherServers: Seq[ActorRef] = Seq()
  var broadcastSequences: Buffer[Int] = Buffer()
  var broadcastsSent: Buffer[Int] = Buffer()
  var broadcastsReceived: Buffer[Int] = Buffer()

  var joinChance = 10
  var leaveChance = 10
  var broadcastChance = 50

  def receive() = {
      case Prime(servers) =>
        otherServers = servers
        broadcastSequences = Buffer.fill(numNodes){ 0 }
        broadcastsSent = Buffer.fill(numNodes){ 0 }
        broadcastsReceived = Buffer.fill(numNodes){ 0 }
        directWrite(myNodeID, Seq(self))
      case Command() =>
        //perform an action
        statistics(sender)
        command
      case Broadcast(groupID, senderSequence) =>
        //receive broadcast and record statistics
        val senderID = gatherIDFromName(sender.path.name)
        broadcastStatistics(groupID, senderID, senderSequence)
        broadcastsReceived(senderID) += 1
        broadcastSequences(senderID) = senderSequence
  }

  private def command() = {
    val sample = generator.nextInt(100)
    if (sample < joinChance) {
      joinRandomGroup
    } else if (sample < joinChance + leaveChance) {
      leaveRandomGroup
    } else if (sample < joinChance + leaveChance + broadcastChance) {
      broadcastToRandomGroup
    }
  }

  private def joinRandomGroup() = {
    if (myGroups.length < otherServers.length) {
      //find a group to join
      var groupID = BigInt(generator.nextInt(otherServers.length))
      while (myGroups.contains(groupID)) {
        groupID = BigInt(generator.nextInt(otherServers.length))
      }
      
      //read current members of group and add self
      var serversInGroup: Option[Seq[ActorRef]] = directRead(groupID)
      serversInGroup match {
        case Some(servers) =>
          directWrite(groupID, servers :+ self)
          myGroups = myGroups :+ groupID
        case None =>
          stats.misses += 1
      }
    }
  }

  private def leaveRandomGroup() = {
    if (myGroups.length > 0) {
      //find a group to leave
      var groupID = BigInt(generator.nextInt(otherServers.length))
      while (!myGroups.contains(groupID)) {
        groupID = BigInt(generator.nextInt(otherServers.length))
      }

      //read current members of group and remove self
      var serversInGroup: Option[Seq[ActorRef]] = directRead(groupID)
      serversInGroup match {
        case Some(servers) =>
          directWrite(groupID, servers.filter(_ != self))
          myGroups = myGroups.filter(_ != groupID)
        case None =>
          stats.misses += 1
      }
    }
  }

  private def broadcastToRandomGroup() = {
    if (myGroups.length > 0) {
        //find a group to braodcast to
      var groupID = BigInt(generator.nextInt(otherServers.length))
      while (!myGroups.contains(groupID)) {
        groupID = BigInt(generator.nextInt(otherServers.length))
      }

      //read current members of group and broadcast
      var serversInGroup: Option[Seq[ActorRef]] = directRead(groupID)
      serversInGroup match {
        case Some(servers) =>
          stats.broadcasts  += 1
          broadcastSequences(nodeID) += 1
          for (server <- servers)
            if (server != self) {
              server ! Broadcast(groupID, broadcastSequences(nodeID))
              broadcastsSent(gatherIDFromName(server.path.name)) += 1
            }
        case None =>
          stats.misses += 1
      }
    }
  }

  private def statistics(master: ActorRef) = {
    stats.messages += 1
    
    if (stats.messages >= burstSize) {
      master ! BurstAck(myNodeID, stats, broadcastsReceived, broadcastsSent)
      stats = new Stats
      broadcastsReceived = Buffer.fill(numNodes){ 0 }
      broadcastsSent = Buffer.fill(numNodes){ 0 }
    }
  }

  private def broadcastStatistics(groupID: BigInt, senderID: Int, sequence: Int) = {
    if (broadcastSequences(senderID) > sequence) stats.misordered += 1
    if (!myGroups.contains(groupID)) stats.late += 1
  }

  private def gatherIDFromName(name: String): Int = {
    name.split("GroupServer")(1).toInt
  }

  private def directRead(key: BigInt): Option[Seq[ActorRef]] = {
    val result = cellstore.directRead(key)
    if (result.isEmpty) None else
      Some(result.get.asInstanceOf[Seq[ActorRef]])
  }

  private def directWrite(key: BigInt, value: Seq[ActorRef]): Option[Seq[ActorRef]] = {
    val result = cellstore.directWrite(key, value)
    if (result.isEmpty) None else
      Some(result.get.asInstanceOf[Seq[ActorRef]])
  }
}

object GroupServer {
  def props(myNodeID: Int, numNodes: Int, storeServers: Seq[ActorRef], burstSize: Int): Props = {
    Props(classOf[GroupServer], myNodeID, numNodes, storeServers, burstSize)
  }
}
