package mapreduce

import akka.actor.{Actor, ActorRef}

case class Start(mapReduceActivity: String)
case class MapperConfig(activity: String, reducerRouter: ActorRef)
case class ReducerConfig(activity: String, numberMappers: Int, masterActor: ActorRef)
case class MapperInput[K1, V1](k1: K1, v1: V1)
case class ReducerInput[K2, V2](k2: K2, v2: V2)
case class ReducerOutput[V3](v3: V3)
case object Finished