#include "QuadField.h"

namespace GameEngine {
	
	
		QuadField::QuadField(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, std::vector<glm::vec3> positions,
		 std::vector<glm::vec3> colors, float scale) : Quad (vertices, indices, vSize, iSize), m_positions(positions),
		m_colors(colors){

			glGenBuffers(1, &m_instanceVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
			glBufferData(GL_ARRAY_BUFFER, BUFFER_INSTANCES * FLOATS_PER_INSTANCE * 4, nullptr, GL_STREAM_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			prepare();
			addInstanceAttribute(getVAO(), m_instanceVBO, 1, 4, FLOATS_PER_INSTANCE, 0); // col1
			addInstanceAttribute(getVAO(), m_instanceVBO, 2, 4, FLOATS_PER_INSTANCE, 4); // col2
			addInstanceAttribute(getVAO(), m_instanceVBO, 3, 4, FLOATS_PER_INSTANCE, 8); // col3
			addInstanceAttribute(getVAO(), m_instanceVBO, 4, 4, FLOATS_PER_INSTANCE, 12);// col4
			addInstanceAttribute(getVAO(), m_instanceVBO, 5, 3, FLOATS_PER_INSTANCE, 16);// colors
			stop();
		}

		void QuadField::update(Shader& shader){
			shader.use();
			prepare();
			index = 0;
			updateTransformations();
			updateVBO();
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,
				m_positions.size());
			stop();
		}

		void QuadField::updateTransformations(){
			for(unsigned int i=0; i<m_positions.size();i++){
				m_model = glm::mat4();
				m_model = glm::translate(m_model, m_positions[i]);
				m_model = glm::scale(m_model, glm::vec3(m_scale)); 
				m_buffer[index++].push_back(m_model[0][0]);
				m_buffer[index++].push_back(m_model[0][1]);
				m_buffer[index++].push_back(m_model[0][2]);
				m_buffer[index++].push_back(m_model[0][3]);

				m_buffer[index++].push_back(m_model[1][0]);
				m_buffer[index++].push_back(m_model[1][1]);
				m_buffer[index++].push_back(m_model[1][2]);
				m_buffer[index++].push_back(m_model[1][3]);

				m_buffer[index++].push_back(m_model[2][0]);
				m_buffer[index++].push_back(m_model[2][1]);
				m_buffer[index++].push_back(m_model[2][2]);
				m_buffer[index++].push_back(m_model[2][3]);

				m_buffer[index++].push_back(m_model[3][0]);
				m_buffer[index++].push_back(m_model[3][1]);
				m_buffer[index++].push_back(m_model[3][2]);
				m_buffer[index++].push_back(m_model[3][3]);
				m_buffer[index++].push_back(m_colors[i].x);
				m_buffer[index++].push_back(m_colors[i].y);
				m_buffer[index++].push_back(m_colors[i].z);
			}
		}

		void QuadField::prepare() {

			glBindVertexArray(getVAO());
			for (int i = 0; i < 5; i++)
				glEnableVertexAttribArray(i);

		}

		void QuadField::stop(){
			for (int i = 0; i < 5; i++)
				glDisableVertexAttribArray(i);

			glBindVertexArray(0);
		}

		void QuadField::updateVBO(){
		
			glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
			glBufferData(GL_ARRAY_BUFFER, m_positions.size() * FLOATS_PER_INSTANCE, nullptr, GL_STREAM_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_positions.size() * FLOATS_PER_INSTANCE,  &m_buffer[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void QuadField::addInstanceAttribute(int vao, int vbo, int attribute, int dataSize, int dataLength, int offset) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindVertexArray(vao);
			glVertexAttribPointer(attribute, dataSize, GL_FLOAT, false, dataLength * 4, (void *)((size_t)(offset * 4)));
			glVertexAttribDivisor(attribute, 1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
	}

}
