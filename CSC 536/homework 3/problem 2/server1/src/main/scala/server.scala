package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{ActorSystem}

case class Book(title: String, url: String)
case object Flush
case object Done

object Server extends App {
  val system = ActorSystem("MapReduceServer", ConfigFactory.load.getConfig("server"))
  println("Server ready...")
  Thread.sleep(990000)
  system.terminate
}
