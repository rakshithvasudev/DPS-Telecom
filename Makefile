.PHONY: clean All

All:
	@echo "----------Building project:[ Part1 - Release ]----------"
	@cd "Part1" && "$(MAKE)" -f  "Part1.mk"
clean:
	@echo "----------Cleaning project:[ Part1 - Release ]----------"
	@cd "Part1" && "$(MAKE)" -f  "Part1.mk" clean
