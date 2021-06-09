package mapreduce

import akka.actor.{Actor, ActorRef}
import akka.routing.Broadcast

case class Name(name: String, title: String)
case class Word(text: String, bookTitle: String)

class MapActor(reducerRouter: ActorRef) extends Actor {

  def receive = {
    case Book(title: String, url: String) =>
      countNames(title, url)
    case Flush => 
      reducerRouter ! Broadcast(Flush)
  }

  def countNames(title: String, url: String) {
    var bookWords: Array[String] = scala.io.Source.fromURL(url).mkString.split("[^A-Za-z]+")

    bookWords = bookWords.filter((word) => (word.length != 0 && word(0).isUpper)).distinct

    for (i <- 0 until bookWords.length) {
        reducerRouter ! Word(bookWords(i), title)
    }
  }
}
