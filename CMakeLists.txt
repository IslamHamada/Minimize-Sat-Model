cmake_minimum_required(VERSION 3.26)
project(SatSolvingCourse)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

include_directories(EvalMaxSAT/lib/cadical/src)
include_directories(EvalMaxSAT/lib/EvalMaxSAT/src)
include_directories(EvalMaxSAT/lib/MaLib/src)

add_executable(SatSolvingCourse main.cpp
        minisat/core/Solver.cc
        minisat/simp/SimpSolver.cc
        minisat/utils/System.cc

        EvalMaxSAT/lib/cadical/src/analyze.cpp
        EvalMaxSAT/lib/cadical/src/arena.cpp
        EvalMaxSAT/lib/cadical/src/assume.cpp
        EvalMaxSAT/lib/cadical/src/averages.cpp
        EvalMaxSAT/lib/cadical/src/backtrack.cpp
        EvalMaxSAT/lib/cadical/src/backward.cpp
        EvalMaxSAT/lib/cadical/src/bins.cpp
        EvalMaxSAT/lib/cadical/src/block.cpp
        EvalMaxSAT/lib/cadical/src/cadical.cpp
        EvalMaxSAT/lib/cadical/src/ccadical.cpp
        EvalMaxSAT/lib/cadical/src/checker.cpp
        EvalMaxSAT/lib/cadical/src/clause.cpp
        EvalMaxSAT/lib/cadical/src/collect.cpp
        EvalMaxSAT/lib/cadical/src/compact.cpp
        EvalMaxSAT/lib/cadical/src/condition.cpp
        EvalMaxSAT/lib/cadical/src/config.cpp
        EvalMaxSAT/lib/cadical/src/constrain.cpp
        EvalMaxSAT/lib/cadical/src/contract.cpp
        EvalMaxSAT/lib/cadical/src/cover.cpp
        EvalMaxSAT/lib/cadical/src/decide.cpp
        EvalMaxSAT/lib/cadical/src/decompose.cpp
        EvalMaxSAT/lib/cadical/src/deduplicate.cpp
        EvalMaxSAT/lib/cadical/src/elim.cpp
        EvalMaxSAT/lib/cadical/src/ema.cpp
        EvalMaxSAT/lib/cadical/src/extend.cpp
        EvalMaxSAT/lib/cadical/src/external.cpp
        EvalMaxSAT/lib/cadical/src/file.cpp
        EvalMaxSAT/lib/cadical/src/flags.cpp
        EvalMaxSAT/lib/cadical/src/format.cpp
        EvalMaxSAT/lib/cadical/src/gates.cpp
        EvalMaxSAT/lib/cadical/src/instantiate.cpp
        EvalMaxSAT/lib/cadical/src/internal.cpp
        EvalMaxSAT/lib/cadical/src/ipasir.cpp
        EvalMaxSAT/lib/cadical/src/limit.cpp
        EvalMaxSAT/lib/cadical/src/logging.cpp
        EvalMaxSAT/lib/cadical/src/lookahead.cpp
        EvalMaxSAT/lib/cadical/src/lucky.cpp
        EvalMaxSAT/lib/cadical/src/message.cpp
        EvalMaxSAT/lib/cadical/src/minimize.cpp
        EvalMaxSAT/lib/cadical/src/mobical.cpp
        EvalMaxSAT/lib/cadical/src/occs.cpp
        EvalMaxSAT/lib/cadical/src/options.cpp
        EvalMaxSAT/lib/cadical/src/parse.cpp
        EvalMaxSAT/lib/cadical/src/phases.cpp
        EvalMaxSAT/lib/cadical/src/probe.cpp
        EvalMaxSAT/lib/cadical/src/profile.cpp
        EvalMaxSAT/lib/cadical/src/proof.cpp
        EvalMaxSAT/lib/cadical/src/propagate.cpp
        EvalMaxSAT/lib/cadical/src/queue.cpp
        EvalMaxSAT/lib/cadical/src/random.cpp
        EvalMaxSAT/lib/cadical/src/reap.cpp
        EvalMaxSAT/lib/cadical/src/reduce.cpp
        EvalMaxSAT/lib/cadical/src/rephase.cpp
        EvalMaxSAT/lib/cadical/src/report.cpp
        EvalMaxSAT/lib/cadical/src/resources.cpp
        EvalMaxSAT/lib/cadical/src/restart.cpp
        EvalMaxSAT/lib/cadical/src/restore.cpp
        EvalMaxSAT/lib/cadical/src/score.cpp
        EvalMaxSAT/lib/cadical/src/shrink.cpp
        EvalMaxSAT/lib/cadical/src/signal.cpp
        EvalMaxSAT/lib/cadical/src/solution.cpp
        EvalMaxSAT/lib/cadical/src/solver.cpp
        EvalMaxSAT/lib/cadical/src/stats.cpp
        EvalMaxSAT/lib/cadical/src/subsume.cpp
        EvalMaxSAT/lib/cadical/src/terminal.cpp
        EvalMaxSAT/lib/cadical/src/ternary.cpp
        EvalMaxSAT/lib/cadical/src/tracer.cpp
        EvalMaxSAT/lib/cadical/src/transred.cpp
        EvalMaxSAT/lib/cadical/src/util.cpp
        EvalMaxSAT/lib/cadical/src/var.cpp
        EvalMaxSAT/lib/cadical/src/version.cpp
        EvalMaxSAT/lib/cadical/src/vivify.cpp
        EvalMaxSAT/lib/cadical/src/walk.cpp
        EvalMaxSAT/lib/cadical/src/watch.cpp
)

target_link_libraries(SatSolvingCourse -lz)