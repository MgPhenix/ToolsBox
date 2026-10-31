## Changelog :


### Add:

- fonctions clear and contains for unordered_map_l
- some Collider
- queue_l : a simple queue still W.I.P but can be used
- Serialization system
- nlohmann json (will be replaced by a custom parser later)

### Change:

- rename EventSystemV2 to EventSystem (old EventSystem was renamed EventSystemOld)
- Add Marien-Garon as an author of the ToolsBox

### Fix:

- Singleton memory leak
- EventSystem memory leak
- Dumb error in Vector2 & Vector3
- unordered_map_l now create auto create a key when you call map[key] if the key doesn't exist instead of just crashing the program

### Still W.I.P:

- A custom std::unordered_map designed to be more light 
- Natvis system
- Collider
- queue_l