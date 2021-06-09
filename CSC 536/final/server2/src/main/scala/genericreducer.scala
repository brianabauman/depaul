package mapreduce

import scala.collection.mutable.HashMap
import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef}

//to do: does this need more inputs?
class GenericReducerActor[K2, V2, V3] extends Actor {

  var master: ActorRef = null

  var aggregate: (K2, V2, HashMap[K2, List[V2]]) => HashMap[K2, List[V2]] = null
  var reduce: (HashMap[K2, List[V2]]) => V3 = null

  var remainingMappers = -1
  var aggregated: HashMap[K2, List[V2]] = HashMap.empty[K2, List[V2]]

  def receive = {
    case ReducerConfig(activity: String, numberMappers: Int, masterActor: ActorRef) =>
      configureReducer(activity, numberMappers, masterActor)
      println(s"debug ${self.path.toString}: reducer configured...")
    case ReducerInput(k2: K2, v2: V2) =>
      aggregated = aggregate(k2, v2, aggregated);
    case Finished =>
      println(s"debug ${self.path.toString}: reducer finished...")
      remainingMappers -= 1
      if (remainingMappers == 0) {
        master ! ReducerOutput[V3](reduce(aggregated))
      }
  }

  def configureReducer(activity: String, numberMappers: Int, masterActor: ActorRef) = {
    master = masterActor
    if (remainingMappers < 0) remainingMappers = numberMappers

    activity match {
      case "wordcounts" =>
        aggregate = WordCount.aggregate[K2, V2] _
        reduce = WordCount.reduce[K2, V2, V3] _
      case "propernouns" =>
        aggregate = ProperNouns.aggregate[K2, V2] _
        reduce = ProperNouns.reduce[K2, V2, V3] _
      case "hyperlinks" =>
        aggregate = Hyperlinks.aggregate[K2, V2] _
        reduce = Hyperlinks.reduce[K2, V2, V3] _
      case _ =>
        println(s"debug ${self.path.toString}: unknown activity...")
    }
  }
}
