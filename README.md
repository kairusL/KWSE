# KWSE
KA MENG (M->W) Super Engine

![KWSE](Assets/ReadMeImages/KWSE.png?raw=true)




# Intro
> KWSE is my custom `game engine` that was using `C++` and `DirectX11`. The game engine is designed and structured in layering order to describe the `framework layer`, `engine layer`, and `application layer`. 

> The engine is for exploring and understanding the steps from building a game engine to develop games.

# Engine Features
Applied supports for redering graphics using `Direct3D11`.
<body>
	<div>
		<h>Rendering features:</h>
		<ul>
			<li>2D Sprite rendering</li>
			<li>Drawing debug lines</li>
			<li>
				Standard shader techniques:
				<ul>
					<li>Blinn-Phong Lighting</li>
					<li>Normal Mapping</li>
					<li>Bump Mapping</li>
					<li>Ambient Occlusion</li>
					<li>Specular Mapping</li>
					<li>Shadow Mapping</li>
					<li>Cube and Environment Mapping</li>
					<li>
						Post Processing:
						<ul>
							<li>Mosaic effect </li>
							<li>Heat-Map effect </li>
							<li>Oil-Painting effect  </li>
						</ul>
					</li>
				</ul>
			</li>
			<li>Loading skinned models</li>
			<li>Playing skeletal animations with animation blending</li>
		</ul>
	</div>
</body>  
  
# Memory Management  
<body>
	<ul>
		<li>Block Allocator -> Pre-allocated memory that serves to aviod memory fragmentation.             </li>
		<li>Typed Allocator -> Allows the user to specify the type of memory used in the block allocator.  </li>
		<li>Handle Pool     -> Handles the validity of pointers to objects.                                </li>	
	</ul>
</body>  

# Component System  
<body>
	<ul>
		<li> Supports components based system for creating game objects.        </li>
		<li> Handle serialized and deserialized for game objects and components.</li>  
	</ul>
</body>  

# Artificial Intelligence  
<body>
	<ul>
		<li> Agent Perception  </li>
		<li> Finite State Machine  </li>
		<li> Goal-driven Behaviour  </li>
		<li> Pathfinding:  
			<ul>
				<li>AStar      </li>
				<li>BFS        </li>
				<li>DFS        </li>
				<li>Dijkstra's </li> 
			</ul>
		</li>
		<li>Steering Behaviour: 
			<ul>
				<li>Arrive Steering Behaviour</li>
				<li>Flee Steering Behaviour</li>
				<li>Group Steering Behaviour
					<ul>
						<li>Alignment Steering Behaviour</li>
						<li>Cohesion Steering Behaviour</li>
						<li>Separation Steering Behaviour </li>
					</ul>
				</li>
				<li>Hide Steering Behaviour</li>
				<li>Obstacle Avoidance steering behavior</li>
				<li>Seek steering behavior</li>
				<li>Wander steering behavior</li>
			</ul>
		</li>		 
	</ul>
</body>   

# Math   
Linear Algebra operations:   
<body>
	<ul>
		<li>Vector2, Vector3, and Vector4  </li>
		<li>Matrix3 and Matrix4            </li>
		<li>Quaternions                    </li>
	</ul>
</body>  

# External Library  
* `Assimp`
* `DirectXTK`
* `FW1FontWrapper`
* `Imgui`
* `RapidJson`
