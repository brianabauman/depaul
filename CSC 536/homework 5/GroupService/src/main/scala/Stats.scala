class Stats {
  var messages: Int = 0
  var broadcasts: Int = 0
  var misses: Int = 0
  var misordered: Int = 0
  var late: Int = 0
  var errors: Int = 0

  def += (right: Stats): Stats = {
    messages += right.messages
    broadcasts += right.broadcasts
    misses += right.misses
    misordered += right.misordered
    late += right.late
    errors += right.errors
    this
  }

  override def toString(): String = {
    s"msgs=$messages broadcasts=$broadcasts miss=$misses misordered=$misordered late=$late err=$errors"
  }
}
