COMMON = common
LIB = lib
MAKE = make
INDEXER = indexer
CRAWLER = crawler
.PHONY: common
.PHONY: lib
.PHONY: indexer
.PHONY: crawler
common:
	$(MAKE) -C $(COMMON)

lib:
	$(MAKE) -C $(LIB)

indexer:
	$(MAKE) -C $(INDEXER)

crawler:
	$(MAKE) -C $(CRAWLER)
clean:
	$(MAKE) -C $(COMMON) clean
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(INDEXER) clean
	$(MAKE) -C $(CRAWLER) clean
