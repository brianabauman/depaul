package mapreduce

import com.typesafe.config.ConfigFactory
import scala.collection.mutable.HashMap

import akka.actor.{Actor, ActorSystem, Props}

object Client extends App {
  val system = ActorSystem("MapReduceClient", ConfigFactory.load.getConfig("client")) 

  //word count example:
  // println(s"${system.name}: Starting word count example...")
  // val wordCountMaster = system.actorOf(
  //   Props[MasterActor[String, String, String, Int, HashMap[String, Int]]],
  //   name = "WordCountMaster")
  // wordCountMaster ! Start("wordcounts")
  // wordCountMaster ! MapperInput[String, String]("a", "fileA.txt")
  // wordCountMaster ! MapperInput[String, String]("b", "fileB.txt")
  // wordCountMaster ! MapperInput[String, String]("c", "fileC.txt")
  // wordCountMaster ! MapperInput[String, String]("d", "fileD.txt")
  // Thread.sleep(5000)
  // wordCountMaster ! Finished
  // Thread.sleep(15000)

  //proper nouns example:
  println(s"${system.name}: Starting proper nouns example...")
  val properNounsMaster = system.actorOf(
    Props[MasterActor[String, String, String, String, HashMap[String, List[String]]]], 
    name = "ProperNounsMaster")
  properNounsMaster ! Start("propernouns")
  properNounsMaster ! MapperInput[String, String]("The Pickwick Papers", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg580.txt")
  properNounsMaster ! MapperInput[String, String]("The Life and Adventures of Martin Chuzzlewit", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg968.txt")
  properNounsMaster ! MapperInput[String, String]("Hunted Down", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg807.txt")
  properNounsMaster ! MapperInput[String, String]("Great Expectations", "http://reed.cs.depaul.edu/lperkovic/csc536/homeworks/gutenberg/pg1400.txt")
  Thread.sleep(5000)
  properNounsMaster ! Finished
  Thread.sleep(15000)

  //hyperlinks example:
  // println(s"${system.name}: Starting hyperlinks example...")
  // val hyperlinksMaster = system.actorOf(
  //   Props[MasterActor[String, String, String, Int, HashMap[String, Int]]],
  //   name = "HyperlinksMaster")
  // hyperlinksMaster ! Start("hyperlinks")
  // hyperlinksMaster ! MapperInput[String, String]("url1", "http://www.google.com")
  // hyperlinksMaster ! MapperInput[String, String]("url2", "http://www.wikipedia.com")
  // hyperlinksMaster ! MapperInput[String, String]("url3", "https://www.nytimes.com")
  // hyperlinksMaster ! MapperInput[String, String]("url4", "https://www.depaul.edu")
  // Thread.sleep(5000)
  // hyperlinksMaster ! Finished
}
