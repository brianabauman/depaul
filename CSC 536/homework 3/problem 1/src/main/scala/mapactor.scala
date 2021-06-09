package mapreduce

import akka.actor.{Actor, ActorRef}

case class Name(name: String, title: String)
case class Word(text: String, bookTitle: String)

class MapActor(reduceActors: List[ActorRef]) extends Actor {
  val numReducers = reduceActors.size

  def receive = {
    case Book(title: String, url: String) =>
      countNames(title, url)
    case Flush => 
      for (reduceActor <- reduceActors) reduceActor ! Flush
  }

  def countNames(title: String, url: String) {
    var bookWords: Array[String] = scala.io.Source.fromURL(url).mkString.split("[^A-Za-z]+")

    bookWords = bookWords.filter((word) => (word.length != 0 && word(0).isUpper)).distinct

    for (i <- 0 until bookWords.length) {
        var word = bookWords(i)
        var index = Math.abs(word.hashCode() % numReducers)

        reduceActors(index) ! Word(word, title)
    }
  }
}
