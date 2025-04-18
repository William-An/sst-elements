import sst
from mhlib import componentlist

# Define the simulation components
verbose = 2

DEBUG_L1 = 0
DEBUG_MEM = 0
DEBUG_LEVEL = 10

cpu = sst.Component("core", "memHierarchy.standardCPU")
cpu.addParams({
    "memFreq" : 100,
    "memSize" : "512MiB",
    "clock" : "1GHz",
    "maxOutstanding" : 10,
    "opCount" : 1000,
    "write_freq" : 25,
    "read_freq" : 75,
})
iface = cpu.setSubComponent("memory", "memHierarchy.standardInterface")

l1cache = sst.Component("l1cache", "memHierarchy.Cache")
l1cache.addParams({
    "access_latency_cycles" : "4",
    "cache_frequency" : "2 Ghz",
    "replacement_policy" : "lru",
    "coherence_protocol" : "MSI",
    "associativity" : "4",
    "cache_line_size" : "64",
    "debug" : DEBUG_L1,
    "debug_level" : DEBUG_LEVEL,
    "verbose" : verbose,
    "L1" : "1",
    "cache_size" : "2KiB"
})

memctrl = sst.Component("memory", "memHierarchy.MemController")
memctrl.addParams({
    "debug" : DEBUG_MEM,
    "debug_level" : DEBUG_LEVEL,
    "clock" : "1GHz",
    "verbose" : verbose,
    "addr_range_end" : 512*1024*1024-1,
})

memory = memctrl.setSubComponent("backend", "memHierarchy.simpleMem")
memory.addParams({
    "access_time" : "1000ns",
    "mem_size" : "512MiB"
})

# Enable statistics
sst.setStatisticLoadLevel(7)
sst.setStatisticOutput("sst.statOutputConsole")
for a in componentlist:
    sst.enableAllStatisticsForComponentType(a)


# Define the simulation links
link_cpu_cache_link = sst.Link("link_cpu_cache_link")
link_cpu_cache_link.connect( (iface, "lowlink", "1000ps"), (l1cache, "highlink", "1000ps") )
link_mem_bus_link = sst.Link("link_mem_bus_link")
link_mem_bus_link.connect( (l1cache, "lowlink", "50ps"), (memctrl, "highlink", "50ps") )
