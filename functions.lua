function getPositions()
function getTile(dx, dy)
function getSprites()
function getExtendedSprites()
function getInputs()

---- Genotype

-- Activation
function sigmoid(x) -- ok

-- Gene
function newGene() -- ok
function copyGene(gene) -- ok

-- Neuron
function newNeuron() -- ok

-- Genome
function newInnovation() -- ok
function newGenome() -- ok
function copyGenome(genome) -- ok
function basicGenome() -- ok
function generateNetwork(genome) -- ok
function evaluateNetwork(network, inputs) -- ok
function containsLink(genes, link) -- ok
function pointMutate(genome) -- ok
function linkMutate(genome, forceBias) -- ok
function nodeMutate(genome) -- ok
function enableDisableMutate(genome, enable) -- ok
function randomNeuron(genes, nonInput) -- ok
function mutate(genome) -- ok
function disjoint(genes1, genes2) -- ok
function weights(genes1, genes2) -- ok
function sameSpecies(genome1, genome2) -- ok
function crossover(g1, g2) -- ok

---- Population

-- Specie
function newSpecies() -- ok
function calculateAverageFitness(species) -- ok
function breedChild(species) -- ok

-- Pool 
function newPool() -- ok
function rankGlobally() -- ok
function totalAverageFitness() -- ok
function cullSpecies(cutToOne) -- ok
function removeStaleSpecies() -- ok
function removeWeakSpecies() -- ok
function addToSpecies(child) -- ok
function newGeneration() -- ok
function initializePool() -- ok
function fitnessAlreadyMeasured() -- ok
function nextGenome() -- ok

----

function initializeRun()
function evaluateCurrent()

function playTop()
function clearJoypad()
function displayGenome(genome)
function writeFile(filename)
function savePool()
function loadFile(filename)
function loadPool()
function onExit()
