package mapreduce

import scala.collection.mutable.HashMap

import akka.actor.{Actor, ActorRef}
import akka.routing.Broadcast
import akka.routing.ConsistentHashingRouter.ConsistentHashMapping

object Hyperlinks { 
  def map[K1, V1](title: K1, url: V1, reducerRouter: ActorRef) = {
    var titleText = title.asInstanceOf[String]
    var urlText = url.asInstanceOf[String]

    var htmlText = ""
    try { 
      htmlText = scala.io.Source.fromURL(urlText, "ISO-8859-1").mkString
    } catch {
      case _: Throwable => //eat the exception
    }

    var regex = raw"((https?:\/\/)([a-zA-Z0-9]*.)?[a-zA-Z0-9]*.(com|org|gov|net|edu))".r

    for(link <- regex.findAllIn(htmlText)) {
      reducerRouter ! ReducerInput[String, Int](link, 1)
    }
  } 

  def hashMapping: ConsistentHashMapping = {
    val partialFunc: PartialFunction[Any, Any] = {
      case ReducerInput(link: String, count: Int) => 
        link
    }

    partialFunc
  }

  def aggregate[K2, V2](link: K2, count: V2, linkCounts: HashMap[K2, List[V2]]): HashMap[K2, List[V2]] = {
    var linkText = link.asInstanceOf[String]
    var countNbr = count.asInstanceOf[Int]
    var linkCountsMap = linkCounts.asInstanceOf[HashMap[String, List[Int]]]

    if (linkCountsMap.contains(linkText)) linkCountsMap(linkText) = countNbr :: linkCountsMap(linkText)
    else linkCountsMap(linkText) = List(countNbr)

    linkCountsMap.asInstanceOf[HashMap[K2, List[V2]]]
  }

  def reduce[K2, V2, V3](linkCounts: HashMap[K2, List[V2]]): V3 = {
    var linkCountsMap = linkCounts.asInstanceOf[HashMap[String, List[Int]]]
    val reducedLinkCounts: HashMap[String, Int] = HashMap.empty[String, Int]
    for ((k, v) <- linkCountsMap) {
      reducedLinkCounts(k) = v.sum
    }
    println(s"debug hyperlinks: reduce complete, sending output to master actor...")
    reducedLinkCounts.asInstanceOf[V3]
  }

  def printResults[V3](linkCounts: V3) = {
    var linkCountsMaps = linkCounts.asInstanceOf[HashMap[String, Int]]
        
    var output = s"Hyperlinks: Finished with ${linkCountsMaps.size} total domains...\n"
    for ((domain, count) <- linkCountsMaps) {
      output += s"Hyperlinks output: ${domain} appeared ${count} times...\n"
    }

    println(output)
  }
}
