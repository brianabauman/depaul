package mapreduce

import scala.collection.mutable.HashMap

import akka.actor.{Actor, ActorRef}
import akka.routing.Broadcast
import akka.routing.ConsistentHashingRouter.ConsistentHashMapping

object WordCount { 
  def map[K1, V1](title: K1, filePath: V1, reducerRouter: ActorRef) = {
    var titleText = title.asInstanceOf[String]
    var filePathText = filePath.asInstanceOf[String]

    var bodyText = scala.io.Source.fromFile(filePathText).getLines.mkString
    var bodyWords: Array[String] = bodyText.split("[^A-Za-z]+")
    bodyWords = bodyWords.filter((word) => (word.length != 0))

    for (i <- 0 until bodyWords.length) {
      reducerRouter ! ReducerInput[String, Int](bodyWords(i), 1)
    }
  } 

  def hashMapping: ConsistentHashMapping = {
    val partialFunc: PartialFunction[Any, Any] = {
      case ReducerInput(word: String, count: Int) => 
        word
    }

    partialFunc
  }

  def aggregate[K2, V2](word: K2, count: V2, wordCounts: HashMap[K2, List[V2]]): HashMap[K2, List[V2]] = {
    var wordText = word.asInstanceOf[String]
    var countNbr = count.asInstanceOf[Int]
    var wordCountsMap = wordCounts.asInstanceOf[HashMap[String, List[Int]]]

    if (wordCountsMap.contains(wordText)) wordCountsMap(wordText) = countNbr :: wordCountsMap(wordText)
    else wordCountsMap(wordText) = List(countNbr)

    wordCountsMap.asInstanceOf[HashMap[K2, List[V2]]]
  }

  def reduce[K2, V2, V3](wordCounts: HashMap[K2, List[V2]]): V3 = {
    var wordCountsMap = wordCounts.asInstanceOf[HashMap[String, List[Int]]]
    val reducedWordCounts: HashMap[String, Int] = HashMap.empty[String, Int]
    for ((k, v) <- wordCountsMap) {
      reducedWordCounts(k) = v.sum
    }
    println(s"debug wordcount: reduce complete, sending output to master actor...")
    reducedWordCounts.asInstanceOf[V3]
  }

  def printResults[V3](wordCounts: V3) = {
    var wordCountsMaps = wordCounts.asInstanceOf[HashMap[String, Int]]
        
    var output = s"WordCount: Finished with ${wordCountsMaps.size} total words...\n"
    for ((word, count) <- wordCountsMaps) {
      output += s"WordCount output: ${word} appeared ${count} times...\n"
    }

    println(output)
  }
}
