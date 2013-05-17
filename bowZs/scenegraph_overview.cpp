	/*

	Innan ärvde klasserna från varandra såhär

					   Model
					   	 |	* vector<Model*> children
						 |	* ModelMatrix
						 |	* ModelMesh
						 |	* Texture
						 |	* Shader
						 |	  void drawModel(P, V, localModelMatrix);
						 |
			-----------------------------
			|							|
		  Scene						GameObject
			  * vector<Player>			|	* position
			  * vector<LightSource> 	|	* direction
						 				|
						 		DynamicGameObject
						 				|	* velocity
						 				|	* angleVelocity
						 				|
						 			  Player
						 			  		* Controller
						 			  		* LightObject* head


==============================================================================


	Nu har vi ny scengraph. Blir lite ny syntax.
	Så här ärver klasserna av varandra nu.


							   Node
								|  * vector<Node*> children
							 	|  * Node* parent
							 	| 	  virtual void draw(P, V, M);
							 	|
		---------------------------------------------------------
		|		 				|								|
	  Model   		 		 LightSource			  	  	Transformation
	    |  * ModelMesh				* glm::vec3 position		| 	* glm::mat4 matrix
	    |  * Texture				* glm::vec3 direction		|
	    |  * Shader			 		* index						|
	  	|														|
	  Scene											---------------------
	  	   * vector<Player*>						|			|		|
		   * vector<LightSource*>				Translation   Scale   Rotation




	- GameObject ärver inte längre från Model
	- GameObject är i princip bara 4 Nodes som är ihopkopplade enligt

				Translation -> Rotation -> Scaling -> Model


		 GameObject
		 	 |	* glm::vec3 position
		 	 |	* glm::vec3 direction
		 	 |	* float phi, theta
		 	 |	* glm::vec3 velocity
			 |	* angleVelocity
			 |
			 |	* Translation
			 |	* Rotation
			 | 	* Scaling
			 | 	* Model
			 |
			 |	  Node* getSceneGraphBranch();
			 |
			 |
		   Player
		  		* Controller
		  		* LightObject* head



	- StaticGameObject är en enklare, effektivare variant av GameObject
	- Används för saker som inte ska röra sig, tex stenar, träd
	- StaticGameObject är i princip bara 2 Nodes som är ihopkopplade enligt

				Transformation -> Model


	*/