package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorSystem, Props}

case class Book(title: String, url: String)
case object Flush
case object Done
object Client extends App {
  val system = ActorSystem("MapReduceClient", ConfigFactory.load.getConfig("client")) 

  println("Client starting...")
  val master = system.actorOf(Props[MasterActor], name = "master")

  master ! Book("The Pickwick Papers", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg580.txt")
  master ! Book("Life And Adventures Of Martin Chuzzlewit", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg968.txt")
  master ! Book("The Life And Adventures Of Nicholas Nickleby", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg967.txt")
  master ! Book("A Christmas Carol", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg19337.txt")

  Thread.sleep(5000)
  master ! Flush
}
