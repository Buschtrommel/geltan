/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/link_p.h
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef LINK_P_H
#define LINK_P_H

#include "link.h"
#include "ppobjectsbase_p.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {

class LinkPrivate : public PPObjectsBasePrivate
{
public:
    LinkPrivate(Link *parent) :
        q_ptr(parent),
        method(Link::Undefined)
    {}

    ~LinkPrivate() {}

    void setHref(const QUrl &nHref)
    {
        if (href != nHref) {
            Q_Q(Link);
            href = nHref;
#ifdef QT_DEBUG
            qDebug() << "Changed href to" << href;
#endif
            Q_EMIT q->hrefChanged(href);
        }
    }

    void setRel(const QString &nRel)
    {
        if (rel != nRel) {
            Q_Q(Link);
            rel = nRel;
#ifdef QT_DEBUG
            qDebug() << "Changed rel to" << rel;
#endif
            Q_EMIT q->relChanged(rel);
        }
    }

    void setMethod(const QString &sMethod)
    {
        if (sMethod == QLatin1String("GET")) {
            setMethod(Link::Get);
        } else if (sMethod == QLatin1String("REDIRECT")) {
            setMethod(Link::Redirect);
        } else if (sMethod == QLatin1String("POST")) {
            setMethod(Link::Post);
        } else {
            setMethod(Link::Undefined);
        }
    }

    void setMethod(Link::MethodType nMethod)
    {
        if (method != nMethod) {
            Q_Q(Link);
            method = method;
#ifdef QT_DEBUG
            qDebug() << "Changed method to" << method;
#endif
            Q_EMIT q->methodChanged(method);
        }
    }

    Link * const q_ptr;
    Q_DECLARE_PUBLIC(Link)
    QUrl href;
    QString rel;
    Link::MethodType method;
};

}
}

#endif // LINK_P_H
