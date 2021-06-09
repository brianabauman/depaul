package tokens;

import akka.actor.{Actor, ActorSystem, Props, ActorRef}
import scala.collection.mutable.HashMap
import scala.collection.mutable.Queue

case class Neighbors(leftNeighbor: ActorRef, rightNeighbor: ActorRef)
case object StartSnapshot
case object LToken
case object RToken
case object Marker

class Node extends Actor {

  private var leftNeighbor: ActorRef = null
  private var rightNeighbor: ActorRef = null

  private var lCount: Int = 0
  private var rCount: Int = 0
  private var isSnapshooting = false
  private var inFlightMessages: HashMap[ActorRef, Queue[Any]] = HashMap.empty[ActorRef, Queue[Any]]
  private var markersReceived: HashMap[ActorRef, Boolean] = HashMap.empty[ActorRef, Boolean]
  private var savedState: String = ""

  def receive = {
    case Neighbors(leftNeighbor, rightNeighbor) => handleNeighbors(leftNeighbor, rightNeighbor)
    case StartSnapshot => handleStartSnapshot()
    case LToken => handleLToken()
    case RToken => handleRToken()
    case Marker => handleMarker()
  }

  def handleNeighbors(leftNeighbor: ActorRef, rightNeighbor: ActorRef): Unit = {
    Thread.sleep(500)

    this.leftNeighbor = leftNeighbor
    this.rightNeighbor = rightNeighbor
  }

  def handleStartSnapshot(): Unit = {
    Thread.sleep(500)

    this.isSnapshooting = true
    this.inFlightMessages(this.leftNeighbor) = Queue.empty[Any]
    this.inFlightMessages(this.rightNeighbor) = Queue.empty[Any]
    this.markersReceived(this.leftNeighbor) = false
    this.markersReceived(this.rightNeighbor) = false
    this.savedState = s"(${this.lCount}, ${this.rCount})"

    this.leftNeighbor ! Marker
    this.rightNeighbor ! Marker
  }

  def handleLToken(): Unit = {
    Thread.sleep(500)   

    if (isSnapshooting && markersReceived(sender) == false) { 
      inFlightMessages(sender).enqueue(LToken)
    }
    
    this.lCount += 1
    this.leftNeighbor ! LToken
  }

  def handleRToken(): Unit = {
    Thread.sleep(500) 

    if (isSnapshooting && markersReceived(sender) == false) { 
      inFlightMessages(sender).enqueue(RToken) 
    }
  
    this.rCount += 1
    this.rightNeighbor ! RToken
  }

  def handleMarker(): Unit = {
    Thread.sleep(500)

    if (!isSnapshooting) {
      this.isSnapshooting = true
      this.inFlightMessages(this.leftNeighbor) = Queue.empty[Any]
      this.inFlightMessages(this.rightNeighbor) = Queue.empty[Any]
      this.markersReceived(this.leftNeighbor) = false
      this.markersReceived(this.rightNeighbor) = false
      this.savedState = s"(${this.lCount}, ${this.rCount})"
      this.markersReceived(sender) = true

      this.leftNeighbor ! Marker
      this.rightNeighbor ! Marker
    } else {
      this.markersReceived(sender) = true   

      var allMarkersReceived = true
      for ((actor, marker) <- this.markersReceived) {
        if (!marker) { allMarkersReceived = false }
      }

      if (allMarkersReceived) { 
        this.isSnapshooting = false 

        var stateMessage: String = s"${self.path.name}: state calculated: ${this.savedState}..."
        for ((actor, queue) <- inFlightMessages) {
          stateMessage += s"\n${self.path.name}: in-flight messages from ${actor.path.name}:"
          for (message <- queue) {
            stateMessage += s"\n${self.path.name}: -- ${message.getClass}"
          }
        }

        println(stateMessage)
      }
    }
  }
}

object Server extends App {
  val system = ActorSystem("Tokens")

  val one = system.actorOf(Props[Node], name = "one")
  val two = system.actorOf(Props[Node], name = "two")
  val three = system.actorOf(Props[Node], name = "three")

  one ! Neighbors(three, two)
  two ! Neighbors(one, three)
  three ! Neighbors(two, one)

  one ! LToken
  one ! RToken

  Thread.sleep(5000)

  one ! StartSnapshot

  Thread.sleep(6000)

  two ! StartSnapshot
}
