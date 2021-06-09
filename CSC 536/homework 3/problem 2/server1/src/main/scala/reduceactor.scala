package mapreduce

import scala.collection.mutable.HashMap
import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef}

class ReduceActor(master: ActorRef) extends Actor {
  var remainingMappers = ConfigFactory.load.getInt("number-mappers")
  var wordTitles: HashMap[String, List[String]] = HashMap.empty[String, List[String]]

  def receive = {
    case Word(word: String, title: String) =>
      if (wordTitles.contains(word)) { 
        wordTitles(word) = title :: wordTitles(word)
      } else {
        wordTitles(word) = List(title)
      }
    case Flush =>
      remainingMappers -= 1
      if (remainingMappers == 0) {
        var reducerOutput = s"${self.path.name} output...\n"
        for ((word, titleList) <- wordTitles) {
          reducerOutput += s"${self.path.name} output: (${word}, ["
          for (title <- titleList) {
            reducerOutput += s"${title}, "
          }
          reducerOutput = reducerOutput.dropRight(2)
          reducerOutput += "])\n"
        }

        println(reducerOutput)

        master ! Done
      }
  }
}
