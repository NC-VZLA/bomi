#ifndef TEXTURERENDERERITEM_HPP
#define TEXTURERENDERERITEM_HPP

#include "stdafx.hpp"

class TextureRendererItem : public QQuickItem {
	Q_OBJECT
public:
	TextureRendererItem(int textures, QQuickItem *parent = 0);
	~TextureRendererItem();
protected:
	typedef QSGGeometry::TexturedPoint2D TexturedPoint2D;
	typedef QSGMaterialShader::RenderState RenderState;
	virtual bool blending() const {return false;}
	virtual char const *const *attributeNames() const;
	virtual const char *vertexShader() const;
	virtual const char *fragmentShader() const = 0;
	virtual void link(QOpenGLShaderProgram *program);
	virtual void bind(const RenderState &state, QOpenGLShaderProgram *program);
	virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
	virtual void beforeUpdate() {}
	virtual void initializeTextures() = 0;
	virtual void updateTexturedPoint2D(TexturedPoint2D *tp) {set(tp, boundingRect(), QRectF(0, 0, 1, 1));}
	static void set(TexturedPoint2D *tp, const QRectF &vtx, const QRectF &txt) {
		set(tp, vtx.topLeft(), txt.topLeft());
		set(++tp, vtx.bottomLeft(), txt.bottomLeft());
		set(++tp, vtx.topRight(), txt.topRight());
		set(++tp, vtx.bottomRight(), txt.bottomRight());
	}
	static void set(TexturedPoint2D *tp, const QPointF &vtx, const QPointF &txt) {
		tp->set(vtx.x(), vtx.y(), txt.x(), txt.y());
	}
	void resetNode();
	void setGeometryDirty(bool dirty = true);
	int textureCount() const {return m_count;}
	GLuint texture(int i) const {return m_textures[i];}
private:
	QSGNode *updatePaintNode(QSGNode *old, UpdatePaintNodeData *data) final;
	struct Shader;	struct Material;	struct Node;	struct Data;
	friend class Node;
	GLuint *m_textures = nullptr, m_count = 0;
	Data *d;
};

#endif // TEXTURERENDERERITEM_HPP