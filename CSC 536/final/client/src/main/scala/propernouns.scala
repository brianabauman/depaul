package mapreduce

import scala.collection.mutable.HashMap

import akka.actor.{Actor, ActorRef}
import akka.routing.Broadcast
import akka.routing.ConsistentHashingRouter.ConsistentHashMapping

object ProperNouns { 
  def map[K1, V1](title: K1, url: V1, reducerRouter: ActorRef) = {
    var titleText = title.asInstanceOf[String]
    var urlText = url.asInstanceOf[String]

    val bookText = scala.io.Source.fromURL(urlText).mkString
    var bookWords: Array[String] = bookText.split("[^A-Za-z]+")
    bookWords = bookWords.filter((word) => (word.length != 0 && word(0).isUpper)).distinct

    for (i <- 0 until bookWords.length) {
      reducerRouter ! ReducerInput[String, String](bookWords(i), titleText)
    }
  }

  def hashMapping: ConsistentHashMapping = {
    val partialFunc: PartialFunction[Any, Any] = {
      case ReducerInput(text: String, bookTitle: String) => 
        text
    }

    partialFunc
  }

  def aggregate[K2, V2](word: K2, title: V2, wordTitles: HashMap[K2, List[V2]]): HashMap[K2, List[V2]] = {
    var wordText = word.asInstanceOf[String]
    var titleText = title.asInstanceOf[String]
    var wordTitlesMap = wordTitles.asInstanceOf[HashMap[String, List[String]]]

    if (wordTitlesMap.contains(wordText)) wordTitlesMap(wordText) = titleText :: wordTitlesMap(wordText)
    else wordTitlesMap(wordText) = List(titleText)

    wordTitlesMap.asInstanceOf[HashMap[K2, List[V2]]]
  }

  def reduce[K2, V2, V3](wordTitles: HashMap[K2, List[V2]]): V3 = {
    var wordTitlesMap = wordTitles.asInstanceOf[HashMap[String, List[String]]]
    println(s"debug propernouns: reduce complete, sending output to master actor...")
    wordTitlesMap.asInstanceOf[V3]
  }

  def printResults[V3](wordTitles: V3) = {
    var wordTitlesMap = wordTitles.asInstanceOf[HashMap[String, List[String]]]

    var output = s"ProperNoun: Finished with ${wordTitlesMap.size} total words...\n"
    for ((word, titleList) <- wordTitlesMap) {
      output += s"ProperNouns output: (${word}, ["
      for (title <- titleList) {
        output += s"${title}, "
      }
      output = output.dropRight(2)
      output += "])\n"
    }

    println(output)
  }
}
