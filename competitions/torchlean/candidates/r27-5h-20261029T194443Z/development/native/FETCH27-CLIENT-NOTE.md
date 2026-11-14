# Source27 fetch diagnosis boundary

At21:22 UTC, research/HANDOFF preliminarily reports run40952423982 hit
HTTP403 in the native-stats donor fetch; Droot canonical artifacts are not yet
present locally. Treat this as unexecuted source preparation, not an algorithm
negative or a zero time. No request is made to cancel the terminal/frozen job.

One concrete code difference may help the owner classify the failure:

- frozen graft_native_stats_v1.fetch sends Accept:text/plain with the standard
  urllib agent;
- the existing official source materializer sends the truthful
  TorchLean-research-readonly/1.0 client identity.

This is an observed client inconsistency, **not evidence that it caused403**.
Before any retry, inspect the original403 body/headers and the official resource
availability state. Consolidating ordinary authorized HTTP-client handling is
different from assuming access permission. Do not switch identities, routes,
credentials, proxies or endpoints to evade a denial. If current authorization
or public availability is not established, retain UNKNOWN and use source12 or
the owned reciprocal/packing routes. Dimpl performs no network retry here.

The earlier legal200snapshot/f92ee2c9 remains available locally for read-only
research and source-hash checks. It does not itself grant current server access
or whole-source public redistribution. Self-owned reciprocal helperv3 has no
source27 dependency, and the prepared row integration uses only exact12.
